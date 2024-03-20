#include "VirtualEncoder.hpp"
#include "State/Position.hpp"

namespace Device
{
    using State::PositionParams;

    VirtualEncoder::VirtualEncoder(float aNormalizedScaleFactor) : IEncoder(aNormalizedScaleFactor)
    {
    }

    void VirtualEncoder::SetCountIncrement(int32_t aCountIncrement)
    {
        mySimulatedIncrement = aCountIncrement;
    }

    void VirtualEncoder::SetDirection(bool aDirection)
    {
        myParams.direction = aDirection;
    }

    PositionParams VirtualEncoder::UpdateMotionParams()
    {
        if(myParams.direction)
        {
            myParams.count += mySimulatedIncrement;
        }
        else
        {
            myParams.count -= mySimulatedIncrement;
        }

        myParams.timestamp += 10;
        return myParams;
    }
} // namespace Device