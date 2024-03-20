#pragma once

#include "../sml.hpp"
#include "Root.hpp"
#include "Slotting.hpp"
#include "Turning.hpp"

using namespace boost::sml;

class TurningSM
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        // clang-format off
            return make_transition_table(

                //root and inherited actions
                *state<Turning> / Action() = state<Turning::WaitForUser::Waiting>
                ,state<Turning> + event<EStopEvent> / Action() = state<EStop>
                ,state<Turning> + event<StopEvent> / Action() = state<Turning::WaitForUser::Waiting>
                ,state<Turning> + event<ExitEvent> / Action() = state<Idle>
                ,state<Turning> + event<Turning::SetSettingsEvent> / Action() = state<Turning::WaitForUser::Waiting>

                //child states
                //WaitForuser
                ,state<Turning::WaitForUser::Waiting> + event<Turning::WaitForUser::Waiting::ReturnToStartEvent> / Action() = state<Turning::ReturnToStart>
                ,state<Turning::WaitForUser::Waiting> + event<Turning::WaitForUser::Waiting::NextPassEvent> / Action() = state<Turning::TurningPass>

                //TurningPass
                ,state<Turning::TurningPass> / Action() = state<Turning::TurningPass::Unretracting>
                ,state<Turning::TurningPass::Unretracting> + event<MoveDoneEvent> / Action() = state<Turning::TurningPass::WaitForSync>
                ,state<Turning::TurningPass::WaitForSync> + event<Turning::TurningPass::WaitForSync::InSyncEvent> / Action() = state<Turning::TurningPass::Moving>
                ,state<Turning::TurningPass::Moving> + event<MoveDoneEvent> / Action() = state<Turning::TurningPass::Moving::Retracting>
                ,state<Turning::TurningPass::Moving::Retracting> + event<MoveDoneEvent> / Action() = state<Turning::WaitForUser::Waiting>

                //ReturnToStart
                ,state<Turning::ReturnToStart> / Action() = state<Turning::ReturnToStart::Retracting>
                ,state<Turning::ReturnToStart::Retracting> + event<MoveDoneEvent> / Action() = state<Turning::ReturnToStart::MovingToStart>
                ,state<Turning::ReturnToStart::MovingToStart> + event<MoveDoneEvent> / Action() = state<Turning::WaitForUser::Waiting>
                

            );
        // clang-format on
    }

private:
};

class MovementSM
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        // clang-format off
        return make_transition_table(
            * state<Idle> / Action() = state<Idle>
            , state<Idle> + event<Movement::SetTurningModeEvent> / Action() = state<TurningSM>
            , state<Idle> + event<Movement::SetSlottingModeEvent> / Action() = state<Slotting>
            , state<EStop> + event<EStop::ResetEvent> / Action() = state<Idle>
            , state<Idle> + event<EStopEvent> / Action() = state<EStop>
        );
        // clang-format on
    }
};