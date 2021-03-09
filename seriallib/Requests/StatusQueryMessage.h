class StatusQueryMessage : public GrblRequest {
public:
    virtual std::string write(){return "?";}
};
