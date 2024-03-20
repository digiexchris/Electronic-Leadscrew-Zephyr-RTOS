#pragma once

#include "Device/Axis.hpp"
#include "Device/IEncoder.hpp"
#include "State/Position.hpp"
#include <cstdarg>

namespace Machine::Manager
{
/**
The main sync state and motion functionality*/

template <typename MainSpindleEncoder>
class Manager //: public Machine::FSM::BaseFSM
{
    // static_assert((Device::IsEncoder<MainSpindleEncoder>::value), "The Manager template type
    // MainSpindleEncoder must derive from IEncoder");

public:
    explicit Manager(MainSpindleEncoder& aMainSpindleEncoder)
        : myMainSpindleEncoder(aMainSpindleEncoder)
    {
        // start the fsm
        //start();
    }
    virtual void Update() = 0;
    virtual void GenerateMoves() = 0;

protected:
    MainSpindleEncoder& myMainSpindleEncoder;
};

} // namespace Machine::Manager