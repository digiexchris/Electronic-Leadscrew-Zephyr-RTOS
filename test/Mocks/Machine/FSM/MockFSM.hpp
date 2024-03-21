#include "Logging/Logger.hpp"
#include "Machine/FSM/Base.hpp"
#include "Machine/FSM/test_fsm.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/trompeloeil.hpp>

namespace Mocks::Machine::FSM
{

class MockFSM : public TestFSM
{
public:
    MAKE_MOCK0(ExecuteStart, void());
    MAKE_MOCK0(ExecuteSetTurnMode, void());
    MAKE_MOCK1(ExecuteStartAt, void(int));
    MAKE_MOCK0(ExecuteStop, void());
    MAKE_MOCK1(ExecuteStopAt, void(int));
    MAKE_MOCK0(ExecuteEStop, void());
    MAKE_MOCK0(ExecuteReset, void());
};

class MockBaseFSM : public MockFSM
{
public:
};
} // namespace Mocks::Machine::FSM