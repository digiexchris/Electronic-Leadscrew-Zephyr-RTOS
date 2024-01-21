
#include "etl/queue.h"
#include "etl/fsm.h"
#include "etl/message_packet.h"

#include <iostream>
#include <string>

  Machine::Machine()
    : fsm(MACHINE_MODE_ROUTER_ID)
  {
  }

  //***************************************************************************
  // The overridden virtual receive function.
  //***************************************************************************
  void Machine::receive(const etl::imessage& msg_) override
  {
    if (accepts(msg_))
    {
      // Place in queue.
      queue.emplace(msg_);

      std::cout << "Queueing message " << int(msg_.get_message_id()) << std::endl;
    }
    else
    {
      std::cout << "Ignoring message " << int(msg_.get_message_id()) << std::endl;
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
      std::cout << "Processing message " << int(msg.get_message_id()) << std::endl;

      // Call the base class's receive function.
      // This will route it to the correct 'on_event' handler.
      etl::fsm::receive(msg);

      queue.pop();
    }
  }


//*****************************************************************************
// State 1.
//*****************************************************************************

  etl::fsm_state_id_t TurnModeState::on_enter_state() override
  {
    std::cout << "  S1 : Enter state" << std::endl;
    return StateId::TURN_MODE; //This returns different in an HFSM, see docs when you convert
  }

  //***************************************************************************
  void TurnModeState::on_exit_state() override
  {
    std::cout << "  S1 : Exit state" << std::endl;
  }

  //***************************************************************************
  etl::fsm_state_id_t TurnModeState::on_event(const EStopMessage& msg)
  {
    std::cout << "  S1 : Received message " << int(msg.get_message_id()) << " : '" << msg.i << "'" << std::endl;
    std::cout.flush();
    return StateId::TURN_MODE; //this should transition to the sub-state ESTOP of all movement mode states.
  }

  //***************************************************************************
  etl::fsm_state_id_t TurnModeState::on_event(const ResetMessage& msg)
  {
    std::cout << "  S1 : Received message " << int(msg.get_message_id()) << " : '" << msg.d << "'" << std::endl;
    std::cout.flush();
    return StateId::INIT;
  }

  //***************************************************************************
  etl::fsm_state_id_t TurnModeState::on_event_unknown(const etl::imessage& msg)
  {
    std::cout << "  S1 : Received unknown message " << int(msg.get_message_id()) << std::endl;
    std::cout.flush();
    return StateId::TURN_MODE;
  }
};

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_enter_state() override
  {
    std::cout << "  S2 : Enter state" << std::endl;
    return StateId::INIT; //Restore the last mode and set it here
  }

  //***************************************************************************
  // When we enter this state.
  //***************************************************************************
  void InitState::on_exit_state() override
  {
    std::cout << "  S2 : Exit state" << std::endl;
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event(const SetTurnModeMessage& msg)
  {
    std::cout << "  S2 : Received message " << int(msg.get_message_id()) << " : '" << msg.i << "'" << std::endl;
    return StateId::TURN_MODE;
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event(const EStopMessage& msg)
  {
    std::cout << "  S2 : Received message " << int(msg.get_message_id()) << " : '" << msg.d << "'" << std::endl;
    return StateId::INIT;
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event(const ResetMessage& msg)
  {
    std::cout << "  S2 : Received message " << int(msg.get_message_id()) << " : '" << msg.s << "'" << std::endl;
    return StateId::INIT; // uhh, maybe we don't need this message, but I need to play with the FSM
  }

  //***************************************************************************
  etl::fsm_state_id_t InitState::on_event_unknown(const etl::imessage& msg)
  {
    std::cout << "  S2 : Received unknown message " << int(msg.get_message_id()) << std::endl;
    return StateId::INIT;
  }
