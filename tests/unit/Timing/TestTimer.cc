#include "MockTimer.h"

#include <gmock/gmock.h>

using namespace ::testing;

TEST(Timer, ElapesedTimeAfter2TicksIs2)
{
    MockTimer timer;
    timer.start();
    timer.tick();
    timer.tick();
    EXPECT_EQ(2.0, timer.elapsedTime());
}

