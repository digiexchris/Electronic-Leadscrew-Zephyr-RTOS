#pragma once
#include "State/Position.hpp"
#include <cstdint>

namespace Device
{

class IMotor : public State::Position
{
public:
    explicit IMotor(float aNormalizedScaleFactor) : State::Position(aNormalizedScaleFactor){};

    // Move to a target position, if possible.
    virtual void MoveTo(int32_t aTargetPosition) = 0;

    // Stop now, flushing any remaining motion commands, if possible.
    // If used with a closed loop stepper, this could turn off the enable pin. E-stop style.
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual bool IsEnabled() = 0;
};

} // namespace Device