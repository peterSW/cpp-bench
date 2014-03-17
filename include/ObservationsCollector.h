#pragma once

#include <Timer.h>
#include <Observations.h>
#include <vector>
#include <cstddef>

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
        for(std::size_t i(0); i < m_probSizes.size(); ++i)
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
    std::vector<std::size_t> m_probSizes;
};
