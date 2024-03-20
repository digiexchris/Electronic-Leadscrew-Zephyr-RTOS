#pragma once
#include "IMotor.hpp"
#include "State/Position.hpp"

namespace Device
{

using State::PositionParams;

/**
 * @brief A virtual encoder for motors with no encoder of their own.
 * Basically just reports the same position the motor was asked to move to
 * at the end of it's move (in the case of a dumb motor) or when it was asked to (in the case of a
 * closed loop) or some other implementation (motor implementation dependent of course, these are
 * hypotheticals) Can also be used for 1 axis machines, this could be the other axis and just don't
 * update it's position.*/
class VirtualMotor : public IMotor
{
public:
    explicit VirtualMotor(float aNormalizedScaleFactor = 1.0);
    void MoveTo(int32_t aTargetPosition) override;
    void Disable() override;
    void Enable() override;
    bool IsEnabled() override;

protected:
    // from State::Position
    PositionParams UpdateMotionParams() override;

private:
    int32_t myTargetPosition;
    int32_t mySimulatedCount;
    uint32_t mySimulatedTimestamp;
    bool mySimulatedDirection;
    PositionParams myParams;
    bool enabled = false;
};

} // namespace Device
