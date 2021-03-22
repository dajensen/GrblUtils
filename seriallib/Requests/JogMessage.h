class JogMessage : public GrblRequest {
    std::vector<std::string> &axisvals;
    double loc;
    int feedrate;
public:
    JogMessage(std::vector<std::string> &axisvals, int feedrate) : axisvals(axisvals), loc(loc), feedrate(feedrate) {}
    virtual std::string write() {
        std::string msg = "$J=";
        for(auto axisstr : axisvals) {
            msg += axisstr;
            msg += " ";
        }
        msg += "F" + std::to_string(feedrate);
        return msg;
    }
};
