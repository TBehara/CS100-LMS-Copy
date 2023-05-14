#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

TEST(googletestSetup, expect0) {
    EXPECT_EQ(0, 0);
}