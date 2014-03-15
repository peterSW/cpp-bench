#include "MockTimer.h"
#include <gmock/gmock.h>

using namespace testing;

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

class LinearMockTimedFunctors : public Test
{
public:
    LinearMockTimedFunctors()
        :
        lmtf(mockTimer)
    {}
    
protected:
    MockTimer mockTimer;
    LinearMockTimedFunctor lmtf;
};


TEST_F(LinearMockTimedFunctors, CanSimulateTiming)
{
    const int problemSize(100);
    
    mockTimer.start();
    lmtf(problemSize);
    EXPECT_THAT(mockTimer.elapsedTime(), Eq(problemSize));
}

