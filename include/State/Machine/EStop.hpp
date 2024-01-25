#pragma once
#include <etl/fsm.h>
#include "Messages.hpp"
#include "Machine.hpp"

class EStopState : public etl::fsm_state<Machine, EStopState, MachineStateId::ESTOP, ResetMessage>
{
public:

  etl::fsm_state_id_t on_enter_state() override;
  void on_exit_state() override;
  etl::fsm_state_id_t on_event(const ResetMessage& msg);
  etl::fsm_state_id_t on_event_unknown(const etl::imessage& msg);
};