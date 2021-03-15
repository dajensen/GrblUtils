#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdint.h>
#include <stdlib.h>
#include <termios.h> /* POSIX terminal control definitions */
#include <ncurses.h>
#include <signal.h>
#include <sys/ioctl.h>

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "screen.h"

std::shared_ptr<Screen::ReinitNotifier> Screen::notifier = nullptr;

Screen::Screen(std::shared_ptr<Screen::ReinitNotifier> notifier) : rows(40), cols(80) {
    Screen::notifier = std::shared_ptr<Screen::ReinitNotifier>(notifier);
    RegisterForWinChange();
    Reinit();
}

Screen::~Screen() {
}

void Screen::Reinit() {
    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0) {
        printf("TIOCGWINSZ error");
        rows = LINES;       // Predefined
        cols = COLS;        // Predefined
    }
    else {
        rows = size.ws_row;
        cols = size.ws_col;
    }

    initscr();
    nonl();                         // tell curses not to do NL->CR/NL on output
    noecho();                       // DO NOT echo input
    curs_set(0);

    if (has_colors())
    {
        start_color();
//        init_pair(1, COLOR_YELLOW,     COLOR_BLUE);
//        init_pair(2, COLOR_WHITE,     COLOR_BLUE);
//        init_pair(3, COLOR_WHITE,     COLOR_BLACK);
//        init_pair(4, COLOR_BLUE,     COLOR_BLACK);
//        init_pair(5, COLOR_RED,     COLOR_BLACK);
        init_pair(1, COLOR_WHITE,     COLOR_BLACK);
        init_pair(2, COLOR_WHITE,     COLOR_BLACK);
        init_pair(3, COLOR_WHITE,     COLOR_BLACK);
        init_pair(4, COLOR_WHITE,     COLOR_BLACK);
        init_pair(5, COLOR_WHITE,     COLOR_BLACK);
    }
}

void Screen::finish(int sig){
    endwin();
//    exit(0);
}

void Screen::SigWinChHandler(int sig)
{
    notifier->Set();
}

void Screen::RegisterForWinChange() {
    struct winsize ws;
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigWinChHandler;
    sigaction(SIGWINCH, &sa, NULL);
}
