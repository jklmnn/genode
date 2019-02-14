
class I2c_hid : Acpica::Callback<I2c_hid> {

    private:

        Acpica::Reportstate *_report;

    public:

        I2c_hid(void *report) :
            _report(reinterpret_cast<Acpica::Reportstate *>(report))
        {
            if(_report){
                _report->add_notify(this);
            }
        }

        void handle(ACPI_HANDLE i2c_hid, UINT32 value)
        {}

        static ACPI_STATUS detect(ACPI_HANDLE i2c_hid, UINT32, void *m, void **)
        {
            Acpica::Main *main = reinterpret_cast<Acpica::Main *>(m);
            Genode::uint8_t hid_guid[16] =
            {0x3c, 0xdf, 0xf6, 0xf7, 0x42, 0x67, 0x45, 0x55, 0xad, 0x05, 0xb3, 0x0a, 0x3d, 0x89, 0x38, 0xde};
            ACPI_OBJECT hid_desc;
            ACPI_BUFFER buffer;
//            buffer.Pointer = &hid_desc;
//            buffer.Length = sizeof(hid_desc);
            buffer.Length = ACPI_ALLOCATE_BUFFER;
            ACPI_OBJECT guid[1];
            guid[0].Type = ACPI_TYPE_BUFFER;
            guid[0].Buffer.Length = sizeof(hid_guid);
            guid[0].Buffer.Pointer = hid_guid;
            ACPI_OBJECT_LIST params;
            params.Count = 1;
            params.Pointer = guid;
            Genode::log("I2C HID Device detected");
            ACPI_STATUS status = AcpiEvaluateObjectTyped(i2c_hid, (ACPI_STRING)"_DSM", &params, &buffer, ACPI_TYPE_PACKAGE);
            Genode::log("_DSM: ", status);
            Genode::log(hid_desc.Type, " (", ACPI_TYPE_INTEGER, ")");
            Genode::log(Genode::Hex(hid_desc.Integer.Value));
            return AE_OK;
        }

        void generate(Genode::Xml_generator &xml)
        {}
};
