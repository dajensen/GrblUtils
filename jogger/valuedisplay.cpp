#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>

#include "log.h"
#include "Utils.h"
#include "DoubleObserver.h"
#include "valuedisplay.h"

void ValueDisplay::DataObserved(double val){
    char strbuf[80];
    sprintf(strbuf, "%010.4f", val);
    wattron(win, color);
    mvwaddstr(win, row, col, strbuf);
    wattroff(win, color);
    wrefresh(win);      // Perhaps move this out to the parent?  Or its parent?
}
