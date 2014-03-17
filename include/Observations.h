#pragma once

#include <vector>
#include <cstddef>

struct Observation
{
    std::size_t problemSize;
    double time;
};

typedef std::vector<Observation> Observations;

