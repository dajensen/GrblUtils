#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>

#include "log.h"
#include "Utils.h"
#include "DoubleObserver.h"
#include "valuedisplay.h"
#include "axisreport.h"


AxisReport::AxisReport(WINDOW *mainwin, std::string title, int color, int row_offset, int col_offset) 
    : workspace(nullptr), actual(nullptr), machine(nullptr)
{
    win = subwin(mainwin, WIN_HEIGHT, WIN_WIDTH, row_offset, col_offset);
    wbkgd(win, color);
    box(win, 0, 0);

    std::string spaced_title = " " + title + " ";
    wattron(win, A_BOLD);
    wattron(win, COLOR_PAIR(2));
    mvwaddstr(win, 0, TITLE_OFFSET, spaced_title.c_str());
    wattroff(win, COLOR_PAIR(2));
    wattroff(win, A_BOLD);

    mvwaddstr(win, WORKSPACE_ROW, LABEL_COL, "W: ");
    mvwaddstr(win, ACTUAL_ROW, LABEL_COL, "A: ");
    mvwaddstr(win, MACHINE_ROW, LABEL_COL, "M: ");
    workspace = new ValueDisplay(win, color, WORKSPACE_ROW, VALUE_COL);
    actual = new ValueDisplay(win, color, ACTUAL_ROW, VALUE_COL);
    machine = new ValueDisplay(win, color, MACHINE_ROW, VALUE_COL);
}

void AxisReport::DataObserved(double val) {
    SetVal(val);
}

void AxisReport::SetVal(double d){
    char strbuf[80];
    sprintf(strbuf, "%010.4f", d);
    wattron(win, COLOR_PAIR(2));
    mvwaddstr(win, WORKSPACE_ROW, VALUE_COL, strbuf);
    wattroff(win, COLOR_PAIR(2));
//    mvwaddstr(win, ACTUAL_ROW, VALUE_COL, strbuf);
    Refresh();
}
