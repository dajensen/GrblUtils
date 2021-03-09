#include "log.h"

class OutputWindow {
public:
    static OutputWindow *GetInstance(WINDOW *parent, std::string title, int color, int row, int col, int width, int height);
    void Refresh() {wrefresh(win);}
    void SetPosition(int row, int col, int width, int height);
    static void Log(LogMessageType lmt, std::string str);

private:
    static OutputWindow *pInstance;
    WINDOW *borderwin, *win;
    int row, col, width, height, color;

    OutputWindow(WINDOW *parent, std::string title, int color, int row, int col, int width, int height);
    void AddString(LogMessageType lmt, std::string str);
};
