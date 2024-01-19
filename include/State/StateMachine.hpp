#include <etl/state_chart.h>

#include "State/State.hpp"

class StateMachine : public etl::state_chart<StateMachine, MachineBaseState, StartState, InitCompleteState> {
public:
    StateMachine(); {
        // Define initial state
        set_initial_state<StartState>();
        // Define transitions
        state<StartState>().on_event<EventStart>().transition_to<RunningState>();
        state<RunningState>().on_event<EventStop>().transition_to<StoppedState>();
    }
    // ... other methods and event handlers
};