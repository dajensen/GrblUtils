
class DoubleObserver {
public:
    virtual void DataObserved(double val) = 0;
};

class DoubleObservable {
protected:
    double val;
    std::vector<std::shared_ptr<DoubleObserver>> observers;

    void update_observers() {
        for(std::shared_ptr<DoubleObserver> obs : observers) {
            obs->DataObserved(val);
        }
    }

public:
    DoubleObservable(double val) : val(val) {}
    double Get() {return val;}
    void ChangeBy(double change_amount) {ChangeTo(val + change_amount);}
    void ChangeTo(double new_value) {val = new_value; update_observers();}
    std::string ToString() {return std::to_string(val);}

    void RegisterObserver(std::shared_ptr<DoubleObserver> obs) {
        observers.push_back(obs);
    }
};
