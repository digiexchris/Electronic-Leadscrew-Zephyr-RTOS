#pragma once


namespace Machine::MessageBus
{

enum MessageId {
    START = 1,
    START_RUNNING_AT, //queue up a timer to engage the leadscrew (START) at a specific time (time in this case is the encoder position plus the time it takes move beween the indicated position to the estimated position between encoder pulses)
    STOP_RUNNING_AT,
    STOP,
    SET_TURNING_MODE,
    TRIGGER_ESTOP,
    RESET
};

struct MachineMessageInterface : public etl::imessage
{
};

/* Starts the position tracking loop to make the tool
* follow the encoder. */
struct StartMessage : public etl::message<MessageId::START, MachineMessageInterface>
{
};

/* Starts the position tracking loop to make the tool
* follow the encoder. */
struct SetTurningMode : public etl::message<MessageId::SET_TURNING_MODE, MachineMessageInterface>
{
};

struct StopMessage : public etl::message<MessageId::STOP, MachineMessageInterface>
{
};

struct EStopMessage : public etl::message<MessageId::TRIGGER_ESTOP, MachineMessageInterface>
{
};

struct ResetMessage : public etl::message<MessageId::RESET, MachineMessageInterface>
{
};

} // namespace Machine::MessageBus