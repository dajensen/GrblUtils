class JogMessage : public GrblRequest {
    std::string axis;
    double loc;
    int feedrate;
public:
    JogMessage(std::string axis, double loc, int feedrate) : axis(axis), loc(loc), feedrate(feedrate) {}
    virtual std::string write(){return "$J=" + axis + std::to_string(loc) + " F" + std::to_string(feedrate);}
};
