#include <etl/state_chart.h>

// Define events
struct EventInitComplete {};
struct EventChangeMode {};
struct EventError {};

// Define base state
class MachineBaseState : public etl::state<MachineBaseState, EventInitComplete, EventChangeMode, EventError> {
    // Common state functionality
};

// Define specific states
class StartState : public MachineBaseState {
    // Default state on a cold boot
};

class InitCompleteState : public MachineBaseState {
    // Settings loaded
};

class ErrorState : public MachineBaseState {
    // Fatal error, stop everything
}