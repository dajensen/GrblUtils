
const int KB_X_INC  = 0x01;
const int KB_X_DEC  = 0x02;
const int KB_X_ZERO = 0x04;
const int KB_X_GOTO = 0x08;

const int KB_Y_INC  = 0x10;
const int KB_Y_DEC  = 0x20;
const int KB_Y_ZERO = 0x40;
const int KB_Y_GOTO = 0x80;

const int KB_Z_INC  = 0x100;
const int KB_Z_DEC  = 0x200;
const int KB_Z_ZERO = 0x400;
const int KB_Z_GOTO = 0x800;

const int KB_A_INC  = 0x1000;
const int KB_A_DEC  = 0x2000;
const int KB_A_ZERO = 0x4000;
const int KB_A_GOTO = 0x8000;

const int KB_B_INC  = 0x10000;
const int KB_B_DEC  = 0x20000;
const int KB_B_ZERO = 0x40000;
const int KB_B_GOTO = 0x80000;

const int KB_INC_INCREMENT = 0x100000;
const int KB_INC_DECREMENT = 0x200000;

class Keyboard {
public:
    Keyboard();

    uint32_t Check();
};
