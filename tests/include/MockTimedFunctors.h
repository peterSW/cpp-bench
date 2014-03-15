#pragma once
#include "MockTimer.h"

class MockTimedFunctor
{
    MockTimer &m_mockTimer;

public:
    MockTimedFunctor(MockTimer &mt)
    :
        m_mockTimer(mt)
    {}

protected:
    void tick()
    {
        m_mockTimer.tick();
    }
};

class LinearMockTimedFunctor : public MockTimedFunctor
{
public:
    LinearMockTimedFunctor(MockTimer &mockTimer)
    :
        MockTimedFunctor(mockTimer)
    {}
    
    void operator () (int problemSize)
    {
        for(; problemSize; --problemSize)
        {
            tick();
        }
    }
};

class SqrMockTimedFunctor : public MockTimedFunctor
{
public:
    SqrMockTimedFunctor(MockTimer &mockTimer)
    :
        MockTimedFunctor(mockTimer)
    {}

    void operator () (const int problemSize)
    {
        for(int i(problemSize); i; --i)
        {
            for(int j(problemSize); j; --j)
            {
                tick();
            }
        }
    }
};
