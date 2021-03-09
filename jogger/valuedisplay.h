class ValueDisplay : public DoubleObserver {
    WINDOW *win;
    int color;
    int row;
    int col;

public:
    ValueDisplay(WINDOW *win, int color, int row, int col) : win(win), color(color), row(row), col(col) {}

    virtual void DataObserved(double val);
};