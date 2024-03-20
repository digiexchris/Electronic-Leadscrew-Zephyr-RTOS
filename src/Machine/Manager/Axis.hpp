#pragma once

#include "State/Position.hpp"
#include "Device/IEncoder.hpp"
#include "Device/IMotor.hpp"
#include <cstdarg>
#include <utility>

#include <boost/functional/lightweight_forward_adapter.hpp>

namespace Device 
{

template <typename MotorType>
class Axis : public MotorType
{
    public:
        template <typename... MotorTypeArgs>
        Axis(const char anId, MotorTypeArgs&&... args): myId(anId), MotorType(boost::lightweight_forward_adapter<MotorTypeArgs>(args)...) {
        };
    protected:
        
        char GetId() { return myId; };

    private:
        char myId;
};

} // namespace Device
