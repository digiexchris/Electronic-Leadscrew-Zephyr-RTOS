
#include "etl/queue.h"
#include "etl/fsm.h"
#include "etl/message_packet.h"
#include <zephyr/sys/printk.h>
#include "State/Machine/Machine.hpp"
#include "State/Machine/Idle.hpp"

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_enter_state()
  {
    printk("  S2 : Enter state Idle\n" );
    return etl::ifsm_state::No_State_Change; //Queue the message that sets the saved mode
  }

  void IdleState::on_exit_state()
  {
    printk("  S2 : Exit state Idle\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const StartMessage& msg)
  {
    printk("  S1 : Received message START\n");
    return MachineStateId::RUNNING;
  }

  etl::fsm_state_id_t IdleState::on_event(const StartAtMessage& msg)
  {
    printk("  S1 : Received message START AT\n");
    return MachineStateId::RUNNING;
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const EStopMessage& msg)
  {
    printk("  S1 : Received message ESTOP\n");
    return MachineStateId::ESTOP;
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event(const ResetMessage& msg)
  {
    printk("  S1 : Received message RESET\n");
    return etl::ifsm_state::No_State_Change; // uhh, maybe we don't need this message, but I need to play with the FSM
  }

  //***************************************************************************
  etl::fsm_state_id_t IdleState::on_event_unknown(const etl::imessage& msg)
  {
    printk("  S1 : Received unknown message %d\n", msg.get_message_id());
    return etl::ifsm_state::No_State_Change;
  }
