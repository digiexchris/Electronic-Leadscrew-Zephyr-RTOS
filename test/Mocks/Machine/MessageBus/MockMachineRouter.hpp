#pragma once

/**
* @brief MockMachineRouter
* @details Mocks the MachineRouter class, 
* Allowing testing of the brokers and subscriptions
* Allows expectations against the on_receive methods
*/
#include <catch2/catch_all.hpp>
#include <catch2/trompeloeil.hpp>
#include "Machine/MessageBus/MachineRouter.hpp"
#include "Machine/MessageBus/Messages.hpp"

namespace Mocks::Machine::MessageBus {
using namespace ::Machine::MessageBus;
class MockMachineRouter : public ::Machine::MessageBus::MachineRouter
{
public:
    MAKE_MOCK1(on_receive, void(const StartMessage&));
    MAKE_MOCK1(on_receive, void(const StopMessage&));
    MAKE_MOCK1(on_receive, void(const EStopMessage&));
    MAKE_MOCK1(on_receive, void(const ResetMessage&));
    MAKE_MOCK1(on_receive_unknown, void(const etl::imessage&));
};

class TestQueuedRouter : public QueuedRouter<TestQueuedRouter,10,StartMessage> {
        //MAKE_MOCK1(emplace, void(const etl::imessage&));
        MAKE_MOCK1(on_receive, void(const StartMessage&));
        MAKE_MOCK1(on_receive_unknown, void(const etl::imessage&));
    };

} // namespace Mocks