
class EmptyReply : public GrblReply
{
public:
    EmptyReply(std::string s) : GrblReply(s) {}

    static bool Recognized(std::string raw) {return raw.empty();}
    static std::unique_ptr<GrblReply> CreateInstance(std::string raw) {
        GrblReply *baseptr = (GrblReply *) new EmptyReply(raw);
        return std::unique_ptr<GrblReply>(baseptr);
    }
};
