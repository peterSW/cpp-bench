#include "MockTimer.h"
#include "MockTimedFunctors.h"
#include <ObservationsCollector.h>
#include <Observations.h>
#include <vector>
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


TEST_F(MockTimedFunctors, canCollect)
{
    ObservationsCollector obsCollector(mockTimer);
    std::vector<size_t> probSizes;
    probSizes.push_back(1);
    probSizes.push_back(5);
    obsCollector.setProbSizes(probSizes);
    const Observations obs(obsCollector.observationsOf(lin_mtf));

    for(size_t i(0); i < obs.size(); ++i)
    {
        EXPECT_THAT(obs[i].problemSize, Eq(obs[i].time));
    }
}
