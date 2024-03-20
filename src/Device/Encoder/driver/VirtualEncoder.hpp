#pragma once
#include "State/Position.hpp"
#include "IEncoder.hpp"

namespace Device
{
using State::PositionParams;

/**
 * @brief An encoder simulator. Increments the count and time every time UpdateMotionParams is called*/
class VirtualEncoder : public IEncoder
{
    public:
        explicit VirtualEncoder(float aNormalizedScaleFactor = 1.0);
        void SetCountIncrement(int32_t aCountIncrement);
        void SetDirection(bool aDirection);
    
    protected:
        PositionParams UpdateMotionParams() override;

    private:
        PositionParams myParams {0, false, 0};
        
        int32_t mySimulatedIncrement = 0;
};
} // namespace Device