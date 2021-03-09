#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include "keyboard.h"

const int UP_ARROW = 259;
const int DOWN_ARROW = 258;
const int LEFT_ARROW = 260;
const int RIGHT_ARROW = 261;
const int PG_UP = 339;
const int PG_DOWN = 338;
const int HOME = 262;
const int END = 360;


Keyboard::Keyboard() {
    keypad(stdscr, TRUE);           // enable keyboard mapping 
    cbreak();                       // take input chars one at a time, no wait for \n 
    timeout(100);
    nodelay(stdscr, TRUE);
}

uint32_t Keyboard::Check() {
    uint32_t rv = 0;
    int c;

    while((c = wgetch(stdscr)) != ERR) {
        switch(c) {
            case UP_ARROW:
                rv |= KB_Y_INC;
                break;
            case DOWN_ARROW:
                rv |= KB_Y_DEC;
                break;
            case LEFT_ARROW:
                rv |= KB_X_DEC;
                break;
            case RIGHT_ARROW:
                rv |= KB_X_INC;
                break;
            case HOME:
                rv |= KB_Z_INC;
                break;
            case END:
                rv |= KB_Z_DEC;
                break;
            case PG_UP:
                rv |= KB_A_INC;
                break;
            case PG_DOWN:
                rv |= KB_A_DEC;
                break;
            case '(':
                rv |= KB_B_INC;
                break;
            case ')':
                rv |= KB_B_DEC;
                break;
            case '+':
                rv |= KB_INC_INCREMENT;
                break;
            case '-':
                rv |= KB_INC_DECREMENT;
                break;
            case 'x':
                rv |= KB_X_ZERO;
                break;
            case 'X':
                rv |= KB_X_GOTO;
                break;
            case 'y':
                rv |= KB_Y_ZERO;
                break;
            case 'Y':
                rv |= KB_Y_GOTO;
                break;
            case 'z':
                rv |= KB_Z_ZERO;
                break;
            case 'Z':
                rv |= KB_Z_GOTO;
                break;
            case 'a':
                rv |= KB_A_ZERO;
                break;
            case 'A':
                rv |= KB_A_GOTO;
                break;
            case 'b':
                rv |= KB_B_ZERO;
                break;
            case 'B':
                rv |= KB_B_GOTO;
                break;
        }
    }
    return rv;
}
