
class Keyboard : public Input {
    double increment;

    void increase_increment();
    void decrease_increment();
public:
    constexpr static double DEFAULT_INITIAL_INCREMENT = 1.0;

    Keyboard(double increment);

    virtual Input::Changes Check();
};
