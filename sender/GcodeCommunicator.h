
class GcodeCommunicator : public GrblCommunicator {
    static const int GRBL_RX_BUFFER_SIZE = 100; // Really 128;
    CircularBuffer<int> cb;
    int buffer_used;
    int lines_sent;
    int lines_acked;

public:
    GcodeCommunicator(SerialDataIoImpl &io, GrblReplyDispatcher &dispatcher) : 
        GrblCommunicator(io, dispatcher), cb(128), buffer_used(0), lines_sent(0), lines_acked(0) {}
    bool SendLine(std::string str);
    bool MarkLineReceived();
    bool AllLinesAcked() {return lines_acked == lines_sent;}
};
