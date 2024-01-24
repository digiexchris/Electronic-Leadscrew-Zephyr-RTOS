
#include "etl/queue.h"
#include "etl/fsm.h"
#include "etl/message_packet.h"

#include "State/State.hpp"


  Machine::Machine()
    : fsm(MACHINE_MODE_ROUTER_ID)
  {
  }

  //***************************************************************************
  // The overridden virtual receive function.
  //***************************************************************************
  void Machine::receive(const etl::imessage& msg_)
  {
    if (accepts(msg_))
    {
      // Place in queue.
      queue.emplace(msg_);
      printk("Queueing message %d\n", msg_.get_message_id());
    }
    else
    {
      printk("Message %d not accepted\n", msg_.get_message_id());
    }
  }

  //***************************************************************************
  // The method to call to handle any queued messages.
  //***************************************************************************
  void Machine::process_queue()
  {
    while (!queue.empty())
    {
      message_packet& packet = queue.front();
      etl::imessage& msg = packet.get();
      printk("Processing message %d\n", msg.get_message_id());

      // Call the base class's receive function.
      // This will route it to the correct 'on_event' handler.
      etl::fsm::receive(msg);

      queue.pop();
    }
  }


//*****************************************************************************
// State 1.
//*****************************************************************************

  etl::fsm_state_id_t TurnModeState::on_enter_state()
  {
    printk("  S1 : Enter state TURN MODE\n");
    return No_State_Change; //This returns different in an HFSM, see docs when you convert
  }

  //***************************************************************************
  void TurnModeState::on_exit_state()
  {
    printk("  S1 : Exit state TURN MODE\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t TurnModeState::on_event(const EStopMessage& msg)
  {
    printk("  S1 : Received message ESTOP\n");
    return No_State_Change; //this should transition to the sub-state ESTOP of all movement mode states.
  }

  //***************************************************************************
  etl::fsm_state_id_t TurnModeState::on_event(const ResetMessage& msg)
  {
    printk("  S1 : Received message RESET\n");
    return StateId::INIT;
  }

  //***************************************************************************
  etl::fsm_state_id_t TurnModeState::on_event_unknown(const etl::imessage& msg)
  {
    printk("  S1 : Received unknown message %d\n", msg.get_message_id());
    return No_State_Change;
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_enter_state()
  {
    printk("  S2 : Enter state INIT\n" );
    return No_State_Change; //Restore the last mode and set it here
  }

  void InitState::on_exit_state()
  {
    printk("  S2 : Exit state INIT\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event(const SetTurnModeMessage& msg)
  {
    printk("  S1 : Received message SETTURNMODE\n");
    return StateId::TURN_MODE;
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event(const EStopMessage& msg)
  {
    printk("  S1 : Received message ESTOP\n");
    return No_State_Change;
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event(const ResetMessage& msg)
  {
    printk("  S1 : Received message RESET\n");
    return No_State_Change; // uhh, maybe we don't need this message, but I need to play with the FSM
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event_unknown(const etl::imessage& msg)
  {
    printk("  S1 : Received unknown message %d\n", msg.get_message_id());
    return No_State_Change;
  }
