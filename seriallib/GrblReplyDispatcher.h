class GrblReplyDispatcher {
public:
    GrblReplyDispatcher() {}
    void DispatchGrblReply(std::string raw);
    void RegisterMessageType(GrblReply::recognized_fn recognized, GrblReply::createinstance_fn createinstance, GrblListener &listener);

private:
    class DispatchInfo {
    public:
        GrblReply::recognized_fn Recognized;
        GrblReply::createinstance_fn CreateInstance;
        GrblListener &listener;

        DispatchInfo(GrblReply::recognized_fn recognized, GrblReply::createinstance_fn createinstance, GrblListener &listener) : 
            Recognized(recognized), CreateInstance(createinstance), listener(listener) 
            {}
    };
    std::vector<DispatchInfo> dispatch_info;
};
