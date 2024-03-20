#pragma once
#include "Manager.hpp"
#include "State/Position.hpp"

namespace Machine::Manager
{
template <typename MainSpindleEncoder, typename ZAxisMotor>
class LatheZ : public Manager<MainSpindleEncoder>
{
public:
    LatheZ(MainSpindleEncoder& aMainSpindle, Device::Axis<ZAxisMotor>& anAxis);

    void Update() override;
    void GenerateMoves() override;

protected:
    void GenerateThreadingMoves();
    void GenerateTurningMoves();

    Device::Axis<ZAxisMotor>& myZAxis;
};

template <typename MainSpindleEncoder, typename ZAxisMotor>
LatheZ<MainSpindleEncoder, ZAxisMotor>::LatheZ(MainSpindleEncoder& aMainSpindle,
                                               Device::Axis<ZAxisMotor>& anAxis)
    : Manager<MainSpindleEncoder>(aMainSpindle), myZAxis(anAxis)
{
}

template <typename MainSpindleEncoder, typename ZAxisMotor>
void LatheZ<MainSpindleEncoder, ZAxisMotor>::Update()
{
    // Update the main spindle encoder
    this->myMainSpindleEncoder.Update();
    myZAxis.Update();
    GenerateMoves();
}

template <typename MainSpindleEncoder, typename ZAxisMotor>
void LatheZ<MainSpindleEncoder, ZAxisMotor>::GenerateTurningMoves()
{
    int32_t positionDifference = myZAxis.Diff(this->myMainSpindleEncoder);
    if (positionDifference != 0)
    {

        // NOTE: both positions should be ints at this point, scaled internally
        // this currently is a 1:1 ratio, no gearing.
        myZAxis.MoveTo(myZAxis.GetPosition() - positionDifference);
    }
}

template <typename MainSpindleEncoder, typename ZAxisMotor>
void LatheZ<MainSpindleEncoder, ZAxisMotor>::GenerateThreadingMoves()
{
    // To be implemented with the threading parent state
}

template <typename MainSpindleEncoder, typename ZAxisMotor>
void LatheZ<MainSpindleEncoder, ZAxisMotor>::GenerateMoves()
{
    switch (this->GetStateId())
    {
    case FSM::MachineStateId::IDLE:
        break;
    case FSM::MachineStateId::ESTOP:
        break;
    case FSM::MachineStateId::MOVING: // still have to figure out if we're turning moving or
                                      // threading moving
        GenerateTurningMoves();
        break;
    default:
        break;
    }
}

} // namespace Machine::Manager