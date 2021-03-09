
class GcodeCommunicator : public GrblCommunicator {
    static const int GRBL_RX_BUFFER_SIZE = 128;
    CircularBuffer<int> cb;
    int buffer_used;

public:
    GcodeCommunicator(SerialDataIoImpl &io, GrblReplyDispatcher &dispatcher) : 
        GrblCommunicator(io, dispatcher), cb(128), buffer_used(0) {}
    bool SendLine(std::string str);
    bool MarkLineReceived();
};
