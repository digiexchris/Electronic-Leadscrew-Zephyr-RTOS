#include <zephyr/ztest.h>
#include "../../include/State/State.hpp"
#include <stdint.h>

ZTEST_SUITE(transition_to_turn, NULL, NULL, NULL, NULL, NULL);

ZTEST_F(transition_to_turn, idle_to_turn_mode) {

    Machine fsm;

    TurnModeState myTurnModeState;
    InitState myInitState;

    // The list of states.
    etl::ifsm_state* stateList[] = { &myInitState, &myTurnModeState  };

    // Set up the FSM
    fsm.set_states(stateList, etl::size(stateList));
    fsm.start();

    // Queue all of the messages.
    etl::send_message(fsm, SetTurnModeMessage());

    // De-queue them
    fsm.process_queue();

    etl::fsm_state_id_t currentState = fsm.get_state_id();

    zassert_equal(currentState, StateId::TURN_MODE, "State is not TURN_MODE");

    etl::send_message(fsm, ResetMessage());

    // De-queue them
    fsm.process_queue();

    currentState = fsm.get_state_id();
    zassert_equal(currentState, StateId::INIT, "State is not INIT");

}
