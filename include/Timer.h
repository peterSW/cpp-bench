class Timer
{
    double startTime;

public:
    void start(){
        startTime = currentTime();
    }

    double elapsedTime() {
        return currentTime() - startTime;
    }

private:
    virtual double currentTime() = 0;
};
