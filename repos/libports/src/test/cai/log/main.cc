
#include <base/component.h>

extern "C" void adainit();
extern "C" void _ada_component();

void Component::construct(Genode::Env &env)
{
    env.exec_static_constructors();
    adainit();
    _ada_component();
}
