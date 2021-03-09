
class AxisReport : public DoubleObserver {
public:
    AxisReport(WINDOW *mainwin, std::string title, int color, int row_offset, int col_offset);
    ~AxisReport() {}

    void Refresh() {wrefresh(win);}
    void SetVal(double d);
    std::shared_ptr<DoubleObserver> GetWorkspaceObserver() {return std::shared_ptr<DoubleObserver>(workspace);} 
    std::shared_ptr<DoubleObserver> GetActualObserver() {return std::shared_ptr<DoubleObserver>(actual);} 
    std::shared_ptr<DoubleObserver> GetMachineObserver() {return std::shared_ptr<DoubleObserver>(machine);} 

    virtual void DataObserved(double val); 
    const static int WIN_HEIGHT = 7;
    const static int WIN_WIDTH = 18;
    const static int VALUE_COL = 5;
    const static int LABEL_COL = 2;
    const static int WORKSPACE_ROW = 2;
    const static int ACTUAL_ROW = 3;
    const static int MACHINE_ROW = 4;   
    const static int TITLE_OFFSET = 8;

private:
    WINDOW *win;
    ValueDisplay *workspace;
    ValueDisplay *actual;
    ValueDisplay *machine;
};
