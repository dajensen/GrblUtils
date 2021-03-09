class GcodeCommunicator;

class EmptyListener : public GrblListener{
    GcodeCommunicator &comm;
public:
    EmptyListener(GcodeCommunicator &comm) : comm(comm) {};
    virtual void HandleMessage(GrblReply &msg);

//    int GetFreeSlots() {return planner_slots_free;}
};
