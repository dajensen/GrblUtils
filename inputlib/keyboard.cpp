#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "log.h"
#include "Utils.h"
#include "input.h"
#include "keyboard.h"

const int UP_ARROW = 259;
const int DOWN_ARROW = 258;
const int LEFT_ARROW = 260;
const int RIGHT_ARROW = 261;
const int PG_UP = 339;
const int PG_DOWN = 338;
const int HOME = 262;
const int END = 360;


Keyboard::Keyboard(double increment) :  increment(increment){
    keypad(stdscr, TRUE);           // enable keyboard mapping 
    cbreak();                       // take input chars one at a time, no wait for \n 
    timeout(100);
    nodelay(stdscr, TRUE);
}

Input::Changes Keyboard::Check() {
    Input::Changes changes;
    int c;

    while((c = wgetch(stdscr)) != ERR) {
        switch(c) {
            case UP_ARROW:
                changes.y = increment;
                break;
            case DOWN_ARROW:
                changes.y = -increment;
                break;
            case LEFT_ARROW:
                changes.x = -increment;
                break;
            case RIGHT_ARROW:
                changes.x = increment;
                break;
            case HOME:
                changes.z = increment;
                break;
            case END:
                changes.z = -increment;
                break;
            case PG_UP:
                changes.a = increment;
                break;
            case PG_DOWN:
                changes.a = -increment;
                break;
            case '(':
                changes.b = -increment;
                break;
            case ')':
                changes.b = increment;
                break;
            case '+':
                log(DEBUG, "PLUS");
                increase_increment();
                break;
            case '-':
                log(DEBUG, "MINUS");
                decrease_increment();
                break;
            case 'x':
                changes.events |= INPUT_X_ZERO;
                break;
            case 'X':
                changes.events |= INPUT_X_GOTO;
                break;
            case 'y':
                changes.events |= INPUT_Y_ZERO;
                break;
            case 'Y':
                changes.events |= INPUT_Y_GOTO;
                break;
            case 'z':
                changes.events |= INPUT_Z_ZERO;
                break;
            case 'Z':
                changes.events |= INPUT_Z_GOTO;
                break;
            case 'a':
                changes.events |= INPUT_A_ZERO;
                break;
            case 'A':
                changes.events |= INPUT_A_GOTO;
                break;
            case 'b':
                changes.events |= INPUT_B_ZERO;
                break;
            case 'B':
                changes.events |= INPUT_B_GOTO;
                break;
        }
    }
    return changes;
}

void Keyboard::increase_increment() {
    log(DEBUG, "Increase Increment");
    if(increment < 100) {
        increment *= 10;
    }
}

void Keyboard::decrease_increment() {
    log(DEBUG, "Decrement");
    if(increment > 0.001) {
        increment /= 10;
    }
}
