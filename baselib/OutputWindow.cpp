#include <stdlib.h>
#include <ncurses.h>
#include <string>
#include <vector>

#include "Utils.h"
#include "OutputWindow.h"

OutputWindow *OutputWindow::pInstance = NULL;

OutputWindow *OutputWindow::GetInstance(WINDOW *parent, std::string title, int color, int row, int col, int width, int height) {
    if(!pInstance){
        pInstance = new OutputWindow(parent, title, color, row, col, width, height);
    }
    return pInstance;
}

OutputWindow::OutputWindow(WINDOW *parent, std::string title, int color, int row, int col, int width, int height) :
    row(row), col(col), width(width), height(height), color(color)
{
    log(DEBUG, "Output window at " + std::to_string(row) + " " + std::to_string(col) + "\n");
    borderwin = subwin(parent, height, width, row, col);
    win = subwin(borderwin, height - 2, width - 2, row + 1, col + 1);

    wbkgd(borderwin, color);
    box(borderwin, 0, 0);

    std::string spaced_title = " " + title + " ";
    int xpos = (width - (spaced_title.length() + 1)) / 2;
    wattron(borderwin, A_BOLD);
    mvwaddstr(borderwin, 0, xpos, spaced_title.c_str());
    wattroff(borderwin, A_BOLD);
//    wmove(win, 1, 1);
    wbkgd(win, color);
    scrollok(win, TRUE);

    Refresh();
}

void OutputWindow::SetPosition(int row, int col, int width, int height){
    // Maybe don't do this?  It looks like moving subwindows is discouraged in ncurses
}

void OutputWindow::Log(LogMessageType lmt, std::string str){
    if(pInstance) {
        std::vector<std::string> strings;
        split(str, '\n', strings);
        for(auto s : strings) {
            pInstance->AddString(lmt, trim(s, WHITESPACE));
        }
    }
}

void OutputWindow::AddString(LogMessageType lmt, std::string str) {

    int linecolor = COLOR_PAIR(5);
    switch(lmt) {
    case TO_GRBL:
        linecolor = COLOR_PAIR(3);
        break;
    case FROM_GRBL:
        linecolor = COLOR_PAIR(4);
        break;
    }

    scroll(win);
    wattron(win, linecolor);
    mvwaddstr(win, height - 3, 1, str.c_str());
    wattroff(win, linecolor);
    Refresh();
}
