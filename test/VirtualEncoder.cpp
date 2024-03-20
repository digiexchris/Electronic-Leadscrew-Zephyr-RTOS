//#include <catch2/catch_all.hpp>

#include <zephyr/ztest.h>

ZTEST_SUITE(VirtualEncoder, NULL, NULL, NULL, NULL, NULL);

#include "Device/Encoder/driver/VirtualEncoder.hpp"
#include "Device/State/Position.hpp"

ZTEST(VirtualEncoder, UpdatesWithIncrement)
{
    Device::Encoder::VirtualEncoder encoder(1.0f);
    encoder.SetCountIncrement(10);
    encoder.SetDirection(true);
    encoder.Update();
    zassert_equal(encoder.GetPosition(),10);
    zassert_true(encoder.GetDirection());
    zassert_equal(encoder.GetTimestamp(), 10);
    encoder.SetCountIncrement(20);
    encoder.SetDirection(false);

    encoder.Update();
    zassert_equal(encoder.GetPosition(), -10);
    zassert_false(encoder.GetDirection());
    zassert_equal(encoder.GetTimestamp(), 20);
}