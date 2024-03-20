#include "VirtualMotor.hpp"

namespace Device
{
VirtualMotor::VirtualMotor(float aNormalizedScaleFactor) : IMotor(aNormalizedScaleFactor)
{
}

void VirtualMotor::MoveTo(int32_t aTargetPosition)
{
    if (enabled)
    {
        myParams.count = aTargetPosition;
        Update();
    }
}

void VirtualMotor::Disable()
{
    enabled = false;
}

void VirtualMotor::Enable()
{
    enabled = true;
}

PositionParams VirtualMotor::UpdateMotionParams()
{
    return myParams;
}

bool VirtualMotor::IsEnabled()
{
    return enabled;
}
} // namespace Device