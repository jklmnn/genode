
#include <base/component.h>
#include <base/attached_rom_dataspace.h>
#include <base/signal.h>

namespace I2C_HID
{
    struct Main;
}

struct I2C_HID::Main
{
    Genode::Env &_env;
    Genode::Attached_rom_dataspace _acpi;
    Genode::Signal_handler<Main> _acpi_sigh;

    void detect()
    {
        Genode::log(__func__);
        _acpi.update();
        Genode::log(_acpi.xml());
    }

    Main(Genode::Env &env) :
        _env(env),
        _acpi(env, "i2c_hid"),
        _acpi_sigh(env.ep(), *this, &Main::detect)
    {
        Genode::log("I2C HID device");
        _acpi.update();
        Genode::log(_acpi.xml());
    }
};

void Component::construct(Genode::Env &env)
{
    static I2C_HID::Main main(env);
}

