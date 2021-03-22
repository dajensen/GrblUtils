
const int INPUT_X_ZERO = 0x01;
const int INPUT_X_GOTO = 0x02;

const int INPUT_Y_ZERO = 0x04;
const int INPUT_Y_GOTO = 0x08;

const int INPUT_Z_ZERO = 0x10;
const int INPUT_Z_GOTO = 0x20;

const int INPUT_A_ZERO = 0x40;
const int INPUT_A_GOTO = 0x80;

const int INPUT_B_ZERO = 0x100;
const int INPUT_B_GOTO = 0x200;

class Input {
public:
    class Changes {
    public:
        double x;
        double y;
        double z;
        double a;
        double b;
        uint32_t events;
        uint32_t feedrate;

        Changes() : x(0.0), y(0.0), z(0.0), a(0.0), b(0.0), events(0) {}
    };

    static Input *CreateInstance();
    virtual Changes Check() = 0;
};
