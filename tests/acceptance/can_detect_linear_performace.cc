#include <gmock/gmock.h>

void a_func_with_linear_perf(size_t problemSize)
{
    while(problemSize)
    {
        --problemSize;
    }
}
void a_func_with_non_linear_perf(size_t problemSize)
{
    while(problemSize)
    {
        problemSize /= 2;
    }
}

struct LinearPerfDetector
{
    bool operator () (void (size_t))
    {
        return true;
    }
};

TEST(CanDetect, DISABLED_LinearPerformance)
{
    LinearPerfDetector linDetector;
    EXPECT_TRUE(linDetector(a_func_with_linear_perf));
    EXPECT_FALSE(linDetector(a_func_with_non_linear_perf));
}
