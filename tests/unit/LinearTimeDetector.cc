#include "MockTimer.h"
#include "LinearMockTimedFunctor.h"
#include <gmock/gmock.h>

using namespace testing;

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

