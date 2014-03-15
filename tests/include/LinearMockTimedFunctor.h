#pragma once
#include "MockTimer.h"

class LinearMockTimedFunctor
{
    MockTimer &m_mockTimer;
public:
    LinearMockTimedFunctor(MockTimer &mockTimer)
    : m_mockTimer(mockTimer)
    {}
    
    virtual void operator () (int problemSize)
    {
        for(; problemSize; --problemSize)
        {
            tick();
        }
    }

private:
    void tick()
    {
        m_mockTimer.tick();
    }
};

