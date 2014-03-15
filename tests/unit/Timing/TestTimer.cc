#include "Timer.h"

#include <gmock/gmock.h>

class MockTimer : public Timer
{
    double m_ticks;

public:
    MockTimer()
        : m_ticks(0.0)
    {}
    void tick() {
        m_ticks += 1;
    }
    
private:
    virtual double currentTime()
    {
        return m_ticks;
    }
};

using namespace ::testing;

TEST(Timer, ElapesedTimeAfter2TicksIs2)
{
    MockTimer timer;
    timer.start();
    timer.tick();
    timer.tick();
    EXPECT_EQ(2.0, timer.elapsedTime());
}

