
#include "State/StateMachine.hpp"
#include "State/State.hpp"

StateMachine::StateMachine(); {
        // Define initial state
        set_initial_state<StartState>();
        // Define transitions
        state<StartState>().on_event<EventStart>().transition_to<RunningState>();
        state<InitCompleteState>().on_event<EventStop>().transition_to<StoppedState>();
        state<RunningState>().on_enter<EventError>().
    }