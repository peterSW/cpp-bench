#include "Observations.h"
#include "LinearFitGSL.h"

#include "MockTimedFunctors.h"
#include "MockTimer.h"

#include <vector>

#include <gmock/gmock.h>

MATCHER(Linear, "")
{
    const Observations &obs(arg);
    LinearFitGSL fit(obs);
    return fit.sumSquare() == 0;
}
#include "ObservationsCollector.h"
class Performance
{
    Observations m_obs;

public:
    static Timer *timer;

public:
    template<typename F>
    Performance(F func)
    {
        std::vector<std::size_t> probSizes(3);
        probSizes[0] = 10;
        probSizes[1] = 100;
        probSizes[2] = 1000;
        ObservationsCollector oc(*timer);
        oc.setProbSizes(probSizes);
        m_obs = oc.observationsOf(func);
    }
    
    operator const Observations & () const
    {
        return m_obs;
    }
};

Timer *Performance::timer = NULL;

TEST(LinearRegressionWithGSL, usingObservations)
{
    Observations obs(3);
    obs[0].problemSize = 1;
    obs[0].time = 1;
    obs[1].problemSize = 2;
    obs[1].time = 2;
    obs[2].problemSize = 3;
    obs[2].time = 3;

    LinearFitGSL fit(obs);

    EXPECT_THAT(obs, Linear());
}

TEST(LinearRegressionWithGSL, full)
{
    MockTimer timer;
    Performance::timer = &timer;
    LinearMockTimedFunctor lmtf(timer);
    SqrMockTimedFunctor nlmtf(timer);

    EXPECT_THAT(Performance(lmtf), Linear());
    
    EXPECT_THAT(Performance(nlmtf), ::testing::Not(Linear()));
}

