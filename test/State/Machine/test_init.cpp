#include <zephyr/ztest.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/Running.hpp"
#include "State/Machine/Idle.hpp"
#include "State/Machine/Messages.hpp"
#include <stdint.h>
#include <etl/map.h>

ZTEST_SUITE(transition_to_turn, NULL, NULL, NULL, NULL, NULL);

// ZTEST_F(transition_to_turn, idle_to_start_no_delay) {

//     Machine fsm;

//     Running runningState;
//     InitState initState;

//     // The list of states.
//     etl::ifsm_state* stateList[] = { &initState, &runningState  };

//     // Set up the FSM
//     fsm.set_states(stateList, etl::size(stateList));
//     fsm.start();

//     // Queue all of the messages.
//     etl::send_message(fsm, StartMessage());

//     // De-queue them
//     fsm.process_queue();

//     etl::fsm_state_id_t currentState = fsm.get_state_id();

//     zassert_equal(currentState, MachineStateId::RUNNING, "State is not RUNNING");

//     etl::send_message(fsm, StopMessage());

//     // De-queue them
//     fsm.process_queue();

//     currentState = fsm.get_state_id();
//     zassert_equal(currentState, MachineStateId::IDLE, "State is not IDLE");

// }

ZTEST_F(transition_to_turn, idle_state_changes) {

    //message, expected state
    etl::map<etl::message<sizeof(MessageId)>, MachineStateId, sizeof(MachineStateId)> testCases = {
        {StartMessage(), MachineStateId::RUNNING},
        {StartAtMessage(0), MachineStateId::IDLE},
        {StopMessage(), MachineStateId::IDLE},
        {StopAtMessage(0), MachineStateId::IDLE},
        {EStopMessage(), MachineStateId::ESTOP},
        {ResetMessage(), MachineStateId::IDLE}
    }

    Machine fsm;

    Running runningState;
    IdleState idleState;

    // The list of states.
    etl::ifsm_state* stateList[] = { &idleState, &runningState  };

    // Set up the FSM
    fsm.set_states(stateList, etl::size(stateList));

    for(etl::array[] tc :testCases) {
        fsm.reset();
        fsm.start();

        etl::send_message(fsm, tc[0]);

        // De-queue them
        fsm.process_queue();

        etl::fsm_state_id_t currentState = fsm.get_state_id();

        zassert_equal(currentState, "Resulting State was not " + static_cast<int>(tc[1]);
    }
}