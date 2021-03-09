
class GrblCommunicator {
public:
    GrblCommunicator(SerialDataIoImpl &io, GrblReplyDispatcher &dispatcher) : io(io), bytes_received(0), dispatcher(dispatcher) {}

    bool SendRequest(GrblRequest &req);
    bool SendByte(uint8_t val);
    void CheckIncomingMessages();

protected:
    uint8_t buf[16384];
    int bytes_received;
    SerialDataIoImpl &io;
    const static char terminator[];
    const static int terminator_len;
    GrblReplyDispatcher &dispatcher;

    bool found_terminator(uint8_t c);
};
