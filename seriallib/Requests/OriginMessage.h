class OriginMessage : public GrblRequest {
    std::string axis;
    double loc;
public:
    OriginMessage(std::string axis, double loc) : axis(axis), loc(loc) {}
    virtual std::string write(){return "G92 " + axis + std::to_string(loc);}
//    virtual std::string write(){return "G10 L2 P1 " + axis + std::to_string(loc);}
};