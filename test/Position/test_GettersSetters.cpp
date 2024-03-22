#include <gtest/gtest.h>
#include "Device/State/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/Position/MockPosition.hpp"

using namespace Device::State;

class PositionGettersSettersTest : public DefaultUnitTest {
};

TEST_F(PositionGettersSettersTest, SetPosition) {
    MockPosition encoder;
    PositionParams params = {1000, false, 0};
    encoder.Set(params);

    int32_t position = encoder.GetPosition();
    bool direction = encoder.GetDirection();
    uint32_t timestamp = encoder.GetTimestamp();

    EXPECT_TRUE(position == 1000);
    EXPECT_TRUE(direction == false);
    EXPECT_TRUE(timestamp == 0);
}

TEST_F(PositionGettersSettersTest, GetPosition){
     MockPosition encoder;
     encoder.Set({1000, false, 0});

     int32_t position = encoder.GetPosition();

     EXPECT_TRUE(1000 == position);

     encoder.Set({1001, false, 0});

     position = encoder.GetPosition();

     EXPECT_TRUE(1001 == position);

}

TEST_F(PositionGettersSettersTest, GetDirection)
{
     MockPosition encoder;
     encoder.Set({1000, false, 0});

     bool direction = encoder.GetDirection();

     EXPECT_TRUE(false == direction);

     encoder.Set({1001, true, 0});

     direction = encoder.GetDirection();

     EXPECT_TRUE(true == direction);

}

TEST_F(PositionGettersSettersTest, GetTimestamp)
{
     MockPosition encoder;
     encoder.Set({1000, false, 0});

     uint32_t timestamp = encoder.GetTimestamp();

     EXPECT_TRUE(0 == timestamp);

     encoder.Set({1001, false, 1000});

     timestamp = encoder.GetTimestamp();

     EXPECT_TRUE(1000 == timestamp);

}

TEST_F(PositionGettersSettersTest, GetNormalizedPosition)
{
     MockPosition encoder;
     
     encoder.SetScaleFactor(2);
     encoder.Set({1000, false, 0});

     EXPECT_TRUE(2000 == encoder.GetPosition());
     encoder.Set({1001, false, 1000});
     EXPECT_TRUE(2002 == encoder.GetPosition());

     MockPosition encoder2;
     encoder2.SetScaleFactor(0.5);
     encoder2.Set({1000, false, 0});

     EXPECT_TRUE(500 == encoder2.GetPosition());
     encoder2.Set({1001, false, 1000});
     EXPECT_TRUE(500 == encoder2.GetPosition());
     encoder2.Set({1002, false, 1000});
     EXPECT_TRUE(501 == encoder2.GetPosition());
     encoder2.Set({1003, false, 1000});
     EXPECT_TRUE(501 == encoder2.GetPosition());
     encoder2.Set({1004, false, 1000});
     EXPECT_TRUE(502 == encoder2.GetPosition());
}

TEST_F(PositionGettersSettersTest, 100msPerCountOver10Counts)
{
     MockPosition encoder;
     PositionParams params = {0, false, 1000};
     encoder.Set(params);
     params = {10, false, 2000};
     encoder.Set(params);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_TRUE(100 == period);
}

TEST_F(PositionGettersSettersTest, 100msPerCountOver10CountsNormalized)
{
     MockPosition encoder;
     encoder.SetScaleFactor(0.5);
     PositionParams params = {0, false, 1000};
     encoder.Set(params);
     params = {10, false, 2000};
     encoder.Set(params);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_TRUE(200 == period);
}

TEST_F(PositionGettersSettersTest, GetCountPeriod_WhenNotMoving)
{
     MockPosition encoder;
     encoder.SetScaleFactor(2);
     PositionParams params = {0, false, 1000};
     encoder.Set(params);
     params = {10, false, 2000};
     encoder.Set(params);

     uint16_t period = encoder.GetCountPeriod();

     EXPECT_TRUE(50 == period);
     params = {10, false, 4000};
     
     encoder.Set(params);

     period = encoder.GetCountPeriod();
     EXPECT_TRUE(0 == period);


}

//TODO write a test validating the carry over longer iterations