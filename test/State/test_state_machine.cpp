#include <zephyr/ztest.h>
#include "../../include/State/State.hpp"
#include <stdint.h>

ZTEST_SUITE(state_machine_main_mode_transitions, NULL, NULL, NULL, NULL, NULL);

ZTEST_F(state_machine_main_mode_transitions, idle_to_turn_mode) {

    Machine fsm;

    TurnModeState myTurnModeState;
    InitState myInitState;

    // The list of states.
    etl::ifsm_state* state_list[] = { &myInitState, &myTurnModeState  };

    // Set up the FSM
    fsm.set_states(state_list, 1);
    fsm.start();

    // Queue all of the messages.
    etl::send_message(fsm, SetTurnModeMessage());

    // De-queue them
    fsm.process_queue();

    auto currentState = fsm.get_current_state_id();

    zassert_equal(currentState, StateId::TURN_MODE, "State is not TURN_MODE");

    return 0;

}
