class JogTracker : public GrblListener {

    class JogWatcher : public DoubleObserver {
        std::string axis_name;
        bool changed;
        double changedval;
        JogTracker &tracker;
    public:
        JogWatcher(std::string axis_name, JogTracker &tracker) : tracker(tracker), axis_name(axis_name), changed(false) {}
        virtual void DataObserved(double val); 
        bool IsChanged() {return changed;}
        void SetJogState(double changedval) {JogWatcher::changedval = changedval; changed = true;}
        void ClearJogState() {changed = false; changedval = 0.0;}
        std::string GetString() {return axis_name + std::to_string(changedval);}
    };

    std::vector<std::shared_ptr<JogWatcher>> jogwatchers;
    bool waiting_for_grbl;
    int feedrate;
    GrblCommunicator &comm;

public:
    JogTracker(GrblCommunicator &comm);

    virtual void HandleMessage(GrblReply &msg);
    void SetAxis(AxisNames axis_name, DoubleObservable &axis);
    void SendJogMessage(std::vector<std::string> &axisstrings);
    void CheckForChanges();
};
