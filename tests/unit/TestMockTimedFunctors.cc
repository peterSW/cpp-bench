#include "MockTimer.h"
#include "MockTimedFunctors.h"
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


struct Observation
{
    size_t problemSize;
    double time;
};
typedef std::vector<Observation> Observations;

class ObservationsCollector
{
public:
    ObservationsCollector(Timer &timer)
    :
        m_timer(timer)
    {
    }
    void setProbSizes(const std::vector<size_t> &sizes)
    {
        m_probSizes = sizes;
    }

    template <typename Functor>
    Observations observationsOf(Functor &func)
    {
        Observations obs(m_probSizes.size());
        for(size_t i(0); i < m_probSizes.size(); ++i)
        {
            obs[i] = makeObservation(func, m_probSizes[i]);
        }
        return obs;
    }

    template <typename Functor>
    Observation makeObservation(Functor &func, size_t probSize)
    {
        Observation obs;
        m_timer.start();
        func(probSize);
        obs.time = m_timer.elapsedTime();

        obs.problemSize = probSize;
        return obs;
    }
private:
    Timer &m_timer;
    std::vector<size_t> m_probSizes;
};

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
