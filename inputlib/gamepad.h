
class Gamepad : public Input {
    int sl_x = 0;
    int sl_y = 0;
    int sl_z = 0;
    int sr_x = 0;
    int sr_y = 0;
    int sr_z = 0;
    int hat0x = 0;
    int hat0y = 0;
    int btn_a = 0;
    int btn_b = 0;
    int btn_x = 0;
    int btn_y = 0;
    int btn_l = 0;
    int btn_r = 0;
    int btn_thumbl = 0;
    int btn_thumbr = 0;
    int btn_select = 0;
    int btn_start = 0;
    int btn_mode = 0;
    bool must_sync = false;

    class DevInfo {
    public:
        int fd;
        struct libevdev *evdev;

        DevInfo(int fd, struct libevdev *pEvd) : fd(fd), evdev(pEvd) {}
    };
    std::optional<DevInfo> device_info;

    std::optional<DevInfo> get_xbox_fd(const std::string &inputdir, std::vector<std::string> &detectstrings);
    std::optional<DevInfo> IsDesiredDevice(const std::string fullpath, std::vector<std::string> detectstrings);

    void print_abs_bits(struct libevdev *dev, int axis);
    void print_code_bits(struct libevdev *dev, unsigned int type, unsigned int max);
    void print_bits(struct libevdev *dev);
    void print_props(struct libevdev *dev);
    void print_status();

    int find_greatest(std::vector<int> vals);
    int scale_value(int joystick_val);
    double calc_travel_distance(int val, uint32_t feedrate, unsigned long ms_elapsed);
    uint32_t update_event_mask(uint16_t event, uint16_t value);

public:
    Gamepad();

    virtual bool IsValid() {return (bool)device_info;}
    virtual Input::Changes Check();
};
