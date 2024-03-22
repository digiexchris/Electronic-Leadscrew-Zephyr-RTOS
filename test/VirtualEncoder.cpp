//#include <catch2/catch_all.hpp>

#include <gtest/gtest.h>

// ZTEST_SUITE(VirtualEncoder, NULL, NULL, NULL, NULL, NULL);

#include "Device/Encoder/driver/VirtualEncoder.hpp"
#include "Device/State/Position.hpp"

TEST(VirtualEncoder, UpdatesWithIncrement)
{
    Device::Encoder::VirtualEncoder encoder(1.0f);
    encoder.SetCountIncrement(10);
    encoder.SetDirection(true);
    encoder.Update();
    EXPECT_EQ(encoder.GetPosition(),10);
    EXPECT_TRUE(encoder.GetDirection());
    EXPECT_EQ(encoder.GetTimestamp(), 10);
    encoder.SetCountIncrement(20);
    encoder.SetDirection(false);

    encoder.Update();
    EXPECT_EQ(encoder.GetPosition(), -10);
    EXPECT_FALSE(encoder.GetDirection());
    EXPECT_EQ(encoder.GetTimestamp(), 20);
}