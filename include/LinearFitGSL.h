#pragma once

#include "Observations.h"
#include <gsl/gsl_fit.h>

class LinearFitGSL
{
    double m_sumsq;

public:
    LinearFitGSL(const Observations& obs)
    {
        std::vector<double> probSize(obs.size());
        std::vector<double> time(obs.size());
        for(std::size_t i(0); i < probSize.size(); ++i)
        {
            probSize[i] = obs[i].problemSize;
            time[i] = obs[i].time;
        }
        
        double c0;
        double c1; 
        double cov00;
        double cov01;
        double cov11; 
        
        gsl_fit_linear(&probSize[0], 1, &time[0], 1, time.size(), &c0, &c1, &cov00, &cov01, &cov11, &m_sumsq);
    }
    
    double sumSquare() const
    {
        return m_sumsq;
    }
};

