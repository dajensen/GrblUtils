class Axis : public DoubleObservable {
    std::string axisname;
    GrblCommunicator &comm;
public:
    Axis(std::string axisname, GrblCommunicator &comm) : axisname(axisname), comm(comm), DoubleObservable(0.0) {}
    ~Axis() {}

    bool MoveBy(double increment) {
        ChangeBy(increment);
        JogMessage jog(axisname, val, 1000);
        return comm.SendRequest(jog);
    }

    bool Zero() {
        ChangeTo(0.0);
        OriginMessage coords(axisname, val);        // Trouble - this message should use workspaces.  Then val here should actually be the current MACHINE coordinate
        return comm.SendRequest(coords);
    }

    bool GotoZero() {
        ChangeTo(0.0);
        JogMessage jog(axisname, val, 1000);
        return comm.SendRequest(jog);
    }
 
private:
};