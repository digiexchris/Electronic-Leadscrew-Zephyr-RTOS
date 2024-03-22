#include <gtest/gtest.h>

#include <gtest/trompeloeil.hpp>
#include "Device/State/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/Position/MockPosition.hpp"


using namespace Device::State;

class PositionFunctionsTest : public DefaultUnitTest {
public:
    friend class MockPosition;
protected:
     MockPosition position;
};

TEST_F(PositionFunctionsTest, UpdateMotionParamsCalled)
{
    PositionParams expectedPosition = {300, true, 1};    
    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).LR_RETURN(expectedPosition);

    position.Update();
}

TEST_F(PositionFunctionsTest, Updated)
{
    PositionParams expectedPosition1 = {300, true, 1};

    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).LR_RETURN(expectedPosition1);

    position.Update();

    EXPECT_EQ(position.GetPosition(), 300);
    EXPECT_EQ(position.GetDirection(), true);
    EXPECT_EQ(position.GetTimestamp(), 1);
    
    PositionParams expectedPosition2 = {400, false, 2};
    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).LR_RETURN(expectedPosition2);
    position.Update();

    EXPECT_EQ(position.GetPosition(), 400);
    EXPECT_EQ(position.GetDirection(), false);
    EXPECT_EQ(position.GetTimestamp(), 2);

}

TEST_F(PositionFunctionsTest, GreaterThan)
{
    PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_GT(pos1, pos2);
}

TEST_F(PositionFunctionsTest, LessThan)
{
    PositionParams params1 = {300, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_LT(pos1, pos2);
}

TEST_F(PositionFunctionsTest, Equal)
{
    PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_EQ(pos1, pos2);
}

TEST_F(PositionFunctionsTest, Diff)
{
    PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    EXPECT_EQ(pos1 - pos2, 100);

    EXPECT_EQ(pos2 + pos1, 700);
}