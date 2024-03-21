#pragma once
#include <zephyr/fff.h>
#include "Device/State/Position.hpp"

class MockPosition : public Device::State::Position {

public:
    //MockPosition(float aScaleFactor = 1.0f) : Position(aScaleFactor) {};
    MAKE_MOCK0(UpdateMotionParams, PositionParams(), override);
    
};