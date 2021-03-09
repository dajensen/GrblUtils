
class WelcomeReply : public GrblReply
{
    std::string version;
public:
    WelcomeReply(std::string s) : GrblReply(s) {
        std::vector<std::string> stringparts;
        split(s, ' ', stringparts);
        if(stringparts.size() > 1)
            version = stringparts[1];       
        else
            version = "Unknown";
        printf("+ Welcome\n");
    }

    static bool Recognized(std::string raw) {return startswith(raw, "Grbl");}
    static std::unique_ptr<GrblReply> CreateInstance(std::string raw) {
        GrblReply *baseptr = (GrblReply *) new WelcomeReply(raw);
        return std::unique_ptr<GrblReply>(baseptr);
    }

    std::string GetVersion() {return version;}
};
