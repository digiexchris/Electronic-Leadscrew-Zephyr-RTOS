#ifndef STATE_HPP
#define STATE_HPP
#include "etl/queue.h"
#include "etl/fsm.h"
#include "etl/message_packet.h"
#include <zephyr/sys/printk.h>

enum MessageId {
    SET_TURN_MODE = 1,
    ESTOP,
    RESET
};

#define MACHINE_MODE_ROUTER_ID 1

//*****************************************************************************
// The messages.
//*****************************************************************************
struct SetTurnModeMessage : public etl::message<MessageId::SET_TURN_MODE>
{
};

struct EStopMessage : public etl::message<MessageId::ESTOP>
{
};

struct ResetMessage : public etl::message<MessageId::RESET>
{
};

// struct SetLead : public etl::message<MessageId::SET_LEAD>
// {
//     SetLead(double lead) : lead(lead) {}
//     double lead;
// };

enum StateId
{
  INIT,
  TURN_MODE,
  IDLE
};

//*****************************************************************************
// The Finite State Machine.
//*****************************************************************************
class Machine : public etl::fsm
{
public:

  //***************************************************************************
  // Constructor.
  //***************************************************************************
  Machine()
    : fsm(MACHINE_MODE_ROUTER_ID)
  {
  }

  //***************************************************************************
  // The overridden virtual receive function.
  //***************************************************************************
  void receive(const etl::imessage& msg_) override
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
  void process_queue()
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

private:

  typedef etl::message_packet<SetTurnModeMessage, EStopMessage, ResetMessage> message_packet;

  // The queue of message items.
  etl::queue<message_packet, 10> queue;
};

//*****************************************************************************
// State 1.
//*****************************************************************************
class TurnModeState : public etl::fsm_state<Machine, TurnModeState, StateId::TURN_MODE, EStopMessage, ResetMessage>
{
public:

  //***************************************************************************
  // When we enter this state.
  //***************************************************************************
  etl::fsm_state_id_t on_enter_state() override
  {
    printk("  S1 : Enter state TURN MODE\n");
    return StateId::TURN_MODE; //This returns different in an HFSM, see docs when you convert
  }

  //***************************************************************************
  void on_exit_state() override
  {
    printk("  S1 : Exit state TURN MODE\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event(const EStopMessage& msg)
  {
    printk("  S1 : Received message ESTOP\n");
    return StateId::TURN_MODE; //this should transition to the sub-state ESTOP of all movement mode states.
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event(const ResetMessage& msg)
  {
    printk("  S1 : Received message RESET\n");
    return StateId::INIT;
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg)
  {
    printk("  S1 : Received unknown message %d\n", msg.get_message_id());
    return StateId::TURN_MODE;
  }
};

//*****************************************************************************
// State 2.
//*****************************************************************************
class InitState : public etl::fsm_state<Machine, InitState, StateId::INIT, EStopMessage, SetTurnModeMessage, ResetMessage>
{
public:

  //***************************************************************************
  etl::fsm_state_id_t on_enter_state() override
  {
    printk("  S2 : Enter state INIT\n" );
    return StateId::INIT; //Restore the last mode and set it here
  }

  //***************************************************************************
  // When we enter this state.
  //***************************************************************************
  void on_exit_state() override
  {
    printk("  S2 : Exit state INIT\n");
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event(const SetTurnModeMessage& msg)
  {
    printk("  S1 : Received message SETTURNMODE\n");
    return StateId::TURN_MODE;
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event(const EStopMessage& msg)
  {
    printk("  S1 : Received message ESTOP\n");
    return StateId::TURN_MODE;
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event(const ResetMessage& msg)
  {
    printk("  S1 : Received message RESET\n");
    return StateId::INIT; // uhh, maybe we don't need this message, but I need to play with the FSM
  }

  //***************************************************************************
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg)
  {
    printk("  S1 : Received unknown message %d\n", msg.get_message_id());
    return StateId::INIT;
  }
};

#endif