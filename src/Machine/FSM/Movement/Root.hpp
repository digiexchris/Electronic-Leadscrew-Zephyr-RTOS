#pragma once

#include "../sml.hpp"
#include "CommonEvents.hpp"
#include "Machine/FSM/Movement/Base.hpp"
#include <iostream>

using namespace boost;

class EStop;
class Turning;
class Slotting;

// States
class Idle : public BaseState
{
public:
    struct InitEvent
    {
    };
};

class EStop : public BaseState // consider providing a callback that the implementer can use to
                               // restart the MCU if required.
{
public:
    struct ResetEvent
    {
    };
};

class Movement : public BaseState
{

public:
    struct SetTurningModeEvent
    {
    };

    struct SetSlottingModeEvent
    {
    };
};

// EndStates
