class TopPanel : public GrblListener
{
public:
    TopPanel(WINDOW *parent, int color, int row, int col, int screencols) : screencols(screencols) {}

    virtual void HandleMessage(GrblReply &msg);
    void SetAxes(std::vector<Axis> &axis);
protected:
    int screencols;
    std::vector<AxisReport *> axisreports;
    std::vector<DoubleObservable> workspaces;
    std::vector<DoubleObservable> actuals;
    std::vector<DoubleObservable> machines;
};
