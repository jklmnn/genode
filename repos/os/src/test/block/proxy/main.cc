
#include <base/component.h>
#include <base/heap.h>
#include <block/request_stream.h>
#include <block_session/connection.h>
#include <block_session/block_session.h>
#include <util/reconstructible.h>
#include <base/attached_ram_dataspace.h>

struct Block_session_component : Genode::Rpc_object<Block::Session>, Block::Request_stream
{
    Genode::Entrypoint &_ep;
    Block::Connection &_block;

    Block_session_component(Genode::Region_map &rm,
                            Genode::Dataspace_capability ds,
                            Genode::Entrypoint &ep,
                            Genode::Signal_context_capability sig,
                            Block::Connection &block,
                            Genode::size_t block_size) :
        Request_stream(rm, ds, ep, sig, block_size),
        _ep(ep),
        _block(block)
    {
        _ep.manage(*this);
    }

    ~Block_session_component()
    {
        _ep.dissolve(*this);
    }

    void info(Block::sector_t *count, Genode::size_t *size, Operations *ops) override
    {
        _block.info(count, size, ops);
    }

    void sync() override { }

    Genode::Capability<Tx> tx_cap() override
    {
        return Request_stream::tx_cap();
    }
};

struct Root : Genode::Rpc_object<Genode::Typed_root<Block::Session>>
{
    Genode::Env &_env;
    Genode::Heap _heap;
    Genode::Allocator_avl _alloc;
    Genode::Constructible<Genode::Attached_ram_dataspace> _block_ds;
    Genode::Constructible<Block_session_component> _block_session;
    Genode::Signal_handler<Root> _req_handler;
    Genode::Constructible<Block::Connection> _block_connection;
    Genode::size_t _block_size;

    Block::Request _req;
    bool _set;

    void handler()
    {
        Genode::log(__func__);
        _block_session->with_requests([&] (Block::Request r){
            _req = r;
            _set = true;
            Block::Packet_descriptor packet = Block::Packet_descriptor(
                    _block_connection->tx()->alloc_packet(r.count * _block_size, 0),
                    r.operation == Block::Request::Operation::READ ? Block::Packet_descriptor::READ : Block::Packet_descriptor::WRITE,
                    r.block_number,
                    r.count);
            _block_connection->tx()->submit_packet(packet);
            return Block_session_component::Response::RETRY;
        });
        if(_set){
            _block_session->try_acknowledge([&] (Block_session_component::Ack &ack){
                ack.submit(_req);
                _set = false;
            });
            _block_session->with_requests([&] (Block::Request){
                return Block_session_component::Response::ACCEPTED;
            });
        }
        _block_session->wakeup_client();
    }

    Root(Genode::Env &env) :
        _env(env),
        _heap(env.ram(), _env.rm()),
        _alloc(&_heap),
        _block_ds(),
        _block_session(),
        _req_handler(_env.ep(), *this, &Root::handler),
        _block_connection(),
        _block_size(0),
        _req(),
        _set(false)
    { }

    Genode::Capability<Genode::Session> session(Root::Session_args const &args, Genode::Affinity const &) override
    {
        Genode::log(__func__, " ", args.string());
        Genode::size_t const ds_size = Genode::Arg_string::find_arg(args.string(), "tx_buf_size").ulong_value(0);
        Genode::Ram_quota const ram_quota = Genode::ram_quota_from_args(args.string());

        if(ds_size >= ram_quota.value){
            throw Genode::Insufficient_ram_quota();
        }

        _block_connection.construct(_env, &_alloc, 128 * 1024, "");
        Block::sector_t block_count;
        Block::Session::Operations ops = Block::Session::Operations();
        _block_connection->info(&block_count, &_block_size, &ops);
        _block_ds.construct(_env.ram(), _env.rm(), ds_size);
        _block_session.construct(_env.rm(), _block_ds->cap(), _env.ep(), _req_handler, *_block_connection, _block_size);

        return _block_session->cap();
    }

    void upgrade(Genode::Capability<Genode::Session>, Root::Upgrade_args const &) override
    { }

    void close(Genode::Capability<Genode::Session>) override
    {
        _block_session.destruct();
        _block_ds.destruct();
        _block_connection.destruct();
    }
};

struct Main
{
    Root _root;

    Main (Genode::Env &env) : _root(env)
    {
        Genode::log(__func__);
        env.parent().announce(env.ep().manage(_root));
    }
};

void Component::construct(Genode::Env &env)
{
    static Main inst(env);
}
