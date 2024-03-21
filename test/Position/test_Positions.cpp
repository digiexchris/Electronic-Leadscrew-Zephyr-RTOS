#include <zephyr/ztest.h>

#include "../Mocks/trompeloeil.hpp"
#include "Device/State/Position.hpp"
#include <stdint.h>
#include "TestHelpers/DefaultUnitTest.hpp"
#include "Mocks/State/MockPosition.hpp"

ZTEST_SUITE(VirtualEncoder, NULL, NULL, NULL, NULL, NULL);

class PositionFunctionsTest : public DefaultUnitTest {
public:
    friend class MockPosition;
protected:
     MockPosition position;
};

ZTEST(PositionFunctionsTest, UpdateMotionParamsCalled)
{
    State::PositionParams expectedPosition = {300, true, 1};    
    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).LR_RETURN(expectedPosition);

    position.Update();
}

ZTEST(PositionFunctionsTest, Updated)
{
    State::PositionParams expectedPosition1 = {300, true, 1};

    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).LR_RETURN(expectedPosition1);

    position.Update();

    REQUIRE(position.GetPosition() == 300);
    REQUIRE(position.GetDirection() == true);
    REQUIRE(position.GetTimestamp() == 1);
    
    State::PositionParams expectedPosition2 = {400, false, 2};
    REQUIRE_CALL(position, UpdateMotionParams()).TIMES(1).LR_RETURN(expectedPosition2);
    position.Update();

    REQUIRE(position.GetPosition() == 400);
    REQUIRE(position.GetDirection() == false);
    REQUIRE(position.GetTimestamp() == 2);

}

ZTEST(PositionFunctionsTest, GreaterThan)
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 > pos2);
}

ZTEST(PositionFunctionsTest, LessThan)
{
    State::PositionParams params1 = {300, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 < pos2);
}

ZTEST(PositionFunctionsTest, Equal)
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {400, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 == pos2);
}

ZTEST(PositionFunctionsTest, Diff)
{
    State::PositionParams params1 = {400, true, 1 };
    MockPosition pos1;
    pos1.Set(params1);
    State::PositionParams params2 = {300, true, 1};
    MockPosition pos2;
    pos2.Set(params2);

    REQUIRE(pos1 - pos2 == 100);

    REQUIRE(pos2 + pos1 == 700);
}