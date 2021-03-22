class Axis : public DoubleObservable {
    std::string axisname;
    GrblCommunicator &comm;
public:
    Axis(std::string axisname, GrblCommunicator &comm) : axisname(axisname), comm(comm), DoubleObservable(0.0) {}
    ~Axis() {}

    bool SetZero() {
        OriginMessage coords(axisname, val);        // Trouble - this message should use workspaces.  Then val here should actually be the current MACHINE coordinate
        return comm.SendRequest(coords);
    }
};