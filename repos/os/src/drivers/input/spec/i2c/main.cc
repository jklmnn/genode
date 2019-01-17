
#include <base/component.h>
#include <base/heap.h>

#include <acpica/acpica.h>

extern "C" {
#include "acpi.h"
#include "accommon.h"
#include "acevents.h"
#include "acnamesp.h"
}

extern "C"
void AcpiOsPrintf (const char *fmt, ...){}

extern "C"
void AcpiOsVprintf (const char *fmt, va_list va){}

namespace I2C_HID
{
    struct Main;
}

ACPI_STATUS AcpiOsInstallInterruptHandler(UINT32 irq, ACPI_OSD_HANDLER handler,
                                                  void *context)
{
    Genode::warning(__func__, " not implemented");
    return AE_OK;
}

struct I2C_HID::Main
{
    Genode::Env &_env;
    Genode::Heap _heap;

    static ACPI_STATUS detect(ACPI_HANDLE hid, UINT32, void *context, void **return_bridge)
    {
        I2C_HID::Main *main = reinterpret_cast<I2C_HID::Main *>(context);
        Genode::log("I2C HID device detected ", main);
        return AE_OK;
    }

    Main(Genode::Env &env) :
        _env(env),
        _heap(env.ram(), env.rm())
    {
        Acpica::init(_env, _heap,
                Acpica::Wait_acpi_ready{true},
                Acpica::Act_as_acpi_drv{true});

        ACPI_STATUS status = AcpiInitializeSubsystem();

        if (status != AE_OK) {
            Genode::error("AcpiInitializeSubsystem failed, status=", status);
            return;
        }

        status = AcpiInitializeTables(nullptr, 0, true);
        if (status != AE_OK) {
            Genode::error("AcpiInitializeTables failed, status=", status);
            return;
        }

        status = AcpiLoadTables();
        if (status != AE_OK) {
            Genode::error("AcpiLoadTables failed, status=", status);
            return;
        }

        status = AcpiEnableSubsystem(ACPI_FULL_INITIALIZATION);
        if (status != AE_OK) {
            Genode::error("AcpiEnableSubsystem failed, status=", status);
            return;
        }

        status = AcpiInitializeObjects(ACPI_NO_DEVICE_INIT);
        if (status != AE_OK) {
            Genode::error("AcpiInitializeObjects (no devices) failed, status=", status);
            return;
        }

        /* set APIC mode */
        /*
        status = init_pic_mode();
        if (status != AE_OK) {
            Genode::error("Setting PIC mode failed, status=", status);
            return;
        }
        */

        status = AcpiGetDevices(ACPI_STRING("PNP0C50"), Main::detect, this, nullptr);
        if (status != AE_OK) {
            Genode::error("AcpiGetDevices failed, status=", status);
            return;
        }

    }
};

void Component::construct(Genode::Env &env)
{
    static I2C_HID::Main main(env);
}

