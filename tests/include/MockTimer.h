#pragma once
#include "Timer.h"

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

