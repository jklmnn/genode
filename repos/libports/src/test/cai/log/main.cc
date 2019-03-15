
#include <spark/component.h>

extern "C" void _ada_component();

Spark::Component::Result Spark::Component::construct()
{
    _ada_component();
    return Spark::Component::Result::EXIT;
}
