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

#define MACHINE_MODE_ROUTER_ID 0

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
  IDLE,
  NUMBER_OF_STATES
};

//*****************************************************************************
// The Finite State Machine.
//*****************************************************************************
class Machine : public etl::fsm
{
public:

  Machine();
  void receive(const etl::imessage& msg_) override;
  void process_queue();

private:

  typedef etl::message_packet<SetTurnModeMessage, EStopMessage, ResetMessage> message_packet;
  etl::queue<message_packet, 10> queue;
};

class TurnModeState : public etl::fsm_state<Machine, TurnModeState, StateId::TURN_MODE, EStopMessage, ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const EStopMessage& msg);
  etl::fsm_state_id_t on_event(const ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

class InitState : public etl::fsm_state<Machine, InitState, StateId::INIT, EStopMessage, SetTurnModeMessage, ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const SetTurnModeMessage& msg);
  etl::fsm_state_id_t on_event(const EStopMessage& msg);
  etl::fsm_state_id_t on_event(const ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};

#endif