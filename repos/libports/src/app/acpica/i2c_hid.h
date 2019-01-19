
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
            Genode::log("I2C HID Device detected");
            return AE_OK;
        }

        void generate(Genode::Xml_generator &xml)
        {}
};
