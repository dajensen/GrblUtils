class FileLogger {
    int fd;
    std::string fname;
    
    static FileLogger *pInstance;

    FileLogger(std::string filename);
    void AddString(LogMessageType lmt, std::string str);

public:
    static void Log(LogMessageType lmt, std::string str) {if(pInstance) pInstance->AddString(lmt, str);}
    static FileLogger *GetInstance(std::string filename);
};
