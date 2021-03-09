
class Screen {
public:
    class ReinitNotifier {
        bool should_reinit;
    public:
        ReinitNotifier() : should_reinit(false){}
        void Set() {should_reinit = true;}
        bool Get() {bool rv = should_reinit; should_reinit = false; return rv;}
    };

    Screen(std::shared_ptr<ReinitNotifier> notifier);
    ~Screen();

    void Restore() {finish(0);}
    int GetRows() {return rows;}
    int GetCols() {return cols;}
    void Reinit();
    static void finish(int sig);

private:
    static std::shared_ptr<ReinitNotifier> notifier;
    int rows, cols;

    static void SigWinChHandler(int sig);
    void RegisterForWinChange();
};
