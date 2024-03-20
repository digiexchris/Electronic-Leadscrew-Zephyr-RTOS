#include "VirtualEncoder.hpp"
#include "Device/State/Position.hpp"
#include "Device/Encoder/IEncoder.hpp"

namespace Device::Encoder
{
    using Device::State::PositionParams;

    VirtualEncoder::VirtualEncoder(float aNormalizedScaleFactor) : Device::Encoder::IEncoder(aNormalizedScaleFactor)
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