// #include <catch2/catch_test_macros.hpp>
// #include "State/Position.hpp"
// #include <stdint.h>
// #include "TestHelpers/DefaultUnitTest.hpp"
// #include "Mocks/State/MockPosition.hpp"

// class PositionGettersSettersTest : public DefaultUnitTest {
// protected:
// };

// TEST_CASE_METHOD(PositionGettersSettersTest, "Set Position", "[Position]") {
//     MockPosition encoder;
//     State::PositionParams params = {1000, false, 0};
//     encoder.Set(params);

//     int32_t position = encoder.GetPosition();
//     bool direction = encoder.GetDirection();
//     uint32_t timestamp = encoder.GetTimestamp();

//     REQUIRE(position == 1000);
//     REQUIRE(direction == false);
//     REQUIRE(timestamp == 0);
// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "Get Position", "[Position]"){
//      MockPosition encoder;
//      encoder.Set({1000, false, 0});

//      int32_t position = encoder.GetPosition();

//      REQUIRE(1000 == position);

//      encoder.Set({1001, false, 0});

//      position = encoder.GetPosition();

//      REQUIRE(1001 == position);

// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "position_GetDirection", "[Position]")
// {
//      MockPosition encoder;
//      encoder.Set({1000, false, 0});

//      bool direction = encoder.GetDirection();

//      REQUIRE(false == direction);

//      encoder.Set({1001, true, 0});

//      direction = encoder.GetDirection();

//      REQUIRE(true == direction);

// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "position_GetTimestamp", "[Position]")
// {
//      MockPosition encoder;
//      encoder.Set({1000, false, 0});

//      uint32_t timestamp = encoder.GetTimestamp();

//      REQUIRE(0 == timestamp);

//      encoder.Set({1001, false, 1000});

//      timestamp = encoder.GetTimestamp();

//      REQUIRE(1000 == timestamp);

// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "position_GetNormalizedPosition", "[Position]")
// {
//      MockPosition encoder;
     
//      encoder.SetScaleFactor(2);
//      encoder.Set({1000, false, 0});

//      REQUIRE(2000 == encoder.GetPosition());
//      encoder.Set({1001, false, 1000});
//      REQUIRE(2002 == encoder.GetPosition());

//      MockPosition encoder2;
//      encoder2.SetScaleFactor(0.5);
//      encoder2.Set({1000, false, 0});

//      REQUIRE(500 == encoder2.GetPosition());
//      encoder2.Set({1001, false, 1000});
//      REQUIRE(500 == encoder2.GetPosition());
//      encoder2.Set({1002, false, 1000});
//      REQUIRE(501 == encoder2.GetPosition());
//      encoder2.Set({1003, false, 1000});
//      REQUIRE(501 == encoder2.GetPosition());
//      encoder2.Set({1004, false, 1000});
//      REQUIRE(502 == encoder2.GetPosition());
// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "position_100msPerCountOver10Counts", "[Position]")
// {
//      MockPosition encoder;
//      State::PositionParams params = {0, false, 1000};
//      encoder.Set(params);
//      params = {10, false, 2000};
//      encoder.Set(params);

//      uint16_t period = encoder.GetCountPeriod();

//      REQUIRE(100 == period);
// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "position_100msPerCountOver10CountsNormalized", "[Position]")
// {
//      MockPosition encoder;
//      encoder.SetScaleFactor(0.5);
//      State::PositionParams params = {0, false, 1000};
//      encoder.Set(params);
//      params = {10, false, 2000};
//      encoder.Set(params);

//      uint16_t period = encoder.GetCountPeriod();

//      REQUIRE(200 == period);
// }

// TEST_CASE_METHOD(PositionGettersSettersTest, "position_GetCountPeriod_WhenNotMoving", "[Position]")
// {
//      MockPosition encoder;
//      encoder.SetScaleFactor(2);
//      State::PositionParams params = {0, false, 1000};
//      encoder.Set(params);
//      params = {10, false, 2000};
//      encoder.Set(params);

//      uint16_t period = encoder.GetCountPeriod();

//      REQUIRE(50 == period);
//      params = {10, false, 4000};
     
//      encoder.Set(params);

//      period = encoder.GetCountPeriod();
//      REQUIRE(0 == period);


// }

// //TODO write a test validating the carry over longer iterations