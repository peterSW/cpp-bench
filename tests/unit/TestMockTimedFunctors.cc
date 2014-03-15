#include "MockTimer.h"
#include "MockTimedFunctors.h"
#include <gmock/gmock.h>

using namespace testing;


class MockTimedFunctors : public Test
{
public:
    MockTimedFunctors()
        :
        lin_mtf(mockTimer),
        sqr_mtf(mockTimer)
    {}

protected:
    MockTimer mockTimer;
    LinearMockTimedFunctor lin_mtf;
    SqrMockTimedFunctor sqr_mtf;
};


TEST_F(MockTimedFunctors, CanSimulateTimingOfLinearFunc)
{
    const int problemSize(100);
    
    mockTimer.start();
    lin_mtf(problemSize);
    EXPECT_THAT(mockTimer.elapsedTime(), Eq(problemSize));
}


TEST_F(MockTimedFunctors, CanSimulateTimingOfSqrFunc)
{
    const int problemSize(10);

    mockTimer.start();
    sqr_mtf(problemSize);
    EXPECT_THAT(mockTimer.elapsedTime(), Eq(problemSize*problemSize));
}
