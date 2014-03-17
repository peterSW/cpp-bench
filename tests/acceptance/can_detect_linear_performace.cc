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

TEST(CanAssert,  DISABLED_LinearPerformance)
{
//    using namespace cppbench;
//    ASSERT_THAT(
//        Performance(a_func_with_linear_perf),
//        Linear());
//
//    ASSERT_THAT(
//        Performance(a_func_with_non_linear_perf),
//        Not(Linear());
}
