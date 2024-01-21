#include <etl/hfsm.h>

// // The states.
// Idle        idle;
// Running     running;
// WindingUp   windingUp;
// WindingDown windingDown;
// AtSpeed     atSpeed;

struct StateId
{
  enum
  {
    Started,
    Turning,
    StateCount
  };
};

struct EventId
{
  enum
  {
    Start,
    Stop,
    EStop,
    Stopped,
    Set_Speed,
    Timeout
  };
};

// These are all of the states for this HSFM.
etl::ifsm_state* stateList[StateId::StateCount] =
{
  &idle, &running, &windingUp, &windingDown, &atSpeed
};

// These states are child states of 'Running'.
etl::ifsm_state* childStates[] =
{
  &windingUp, &atSpeed, &windingDown
};

MotorControl motorControl;

running.set_child_states(childStates, etl::size(childStates));

motorControl.Initialise(stateList, etl::size(stateList));