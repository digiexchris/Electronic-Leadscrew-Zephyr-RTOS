
#include "etl/queue.h"
#include "etl/fsm.h"
#include "etl/message_packet.h"
#include <zephyr/sys/printk.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/EStop.hpp"

etl::fsm_state_id_t EStopState::on_enter_state()
  {
    printk("  S2 : Enter state Idle\n" );
    return etl::ifsm_state::No_State_Change; //Queue the message that sets the saved mode
  }

  void EStopState::on_exit_state()
  {
    printk("  S2 : Exit state Idle\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t EStopState::on_event(const ResetMessage& msg)
  {
    printk("  S1 : Received message RESET\n");
    return etl::ifsm_state::No_State_Change; // uhh, maybe we don't need this message, but I need to play with the FSM
  }

  //***************************************************************************
  etl::fsm_state_id_t EStopState::on_event_unknown(const etl::imessage& msg)
  {
    printk("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
  }
