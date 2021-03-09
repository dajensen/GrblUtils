class InitStatusListener : public GrblListener{
    double vals[AxisNames::NUM_AXES];
    bool done;
public:
    InitStatusListener() : done(false) {}
    virtual void HandleMessage(GrblReply &msg);

    bool HaveInitialStatus() {return done;}
    double GetValue(int i);
};
