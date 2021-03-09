class StatusListener : public GrblListener{
    bool &flag;
public:
    StatusListener(bool &flag) : flag(flag) {};
    virtual void HandleMessage(GrblReply &msg);
};
