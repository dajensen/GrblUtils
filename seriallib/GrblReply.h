
class GrblReply;
class GrblReplyDispatcher;

class GrblListener {
public:
    virtual void HandleMessage(GrblReply &msg) = 0;
};


class GrblReply
{
public:
    GrblReply(std::string raw) : raw(raw) {}

    typedef bool (*recognized_fn)(std::string raw);
    typedef std::unique_ptr<GrblReply> (*createinstance_fn)(std::string raw);

protected:
    std::string raw;

};
