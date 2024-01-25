#ifndef STATE_HPP
#define STATE_HPP
#include "etl/queue.h"
#include "etl/hfsm.h"
#include "etl/message_packet.h"
#include <zephyr/sys/printk.h>

#include "State/Machine/Messages.hpp"


#define MACHINE_ROUTER_ID 0

enum MachineStateId
{
  IDLE,
  RUNNING,
  ESTOP,
  NUMBER_OF_STATES
};

//*****************************************************************************
// The Finite State Machine.
//*****************************************************************************
class Machine : public etl::hfsm
{
public:

  Machine();
  void receive(const etl::imessage& msg_) override;
  void process_queue();

private:

  typedef etl::message_packet<StartMessage, StartAtMessage, StopMessage, StopAtMessage, EStopMessage, ResetMessage> message_packet;
  etl::queue<message_packet, 10> queue;
};




#endif