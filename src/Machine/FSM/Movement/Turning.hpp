#pragma once

#include "../sml.hpp"
#include "Base.hpp"
#include "CommonEvents.hpp"
#include <iostream>
#include <map>

using namespace boost::sml;

struct EStop;
struct Idle;

class Turning : public BaseState
{
public:
    struct SetSettingsEvent
    {
        enum class SettingsKey
        {
            Direction = 0,
            RequiresSync,
            DestinationPosition,
            StartPosition,
            FeedRate,
            RapidRate
        };
        std::map<SettingsKey, int32_t> settings;
    };

    // child states
    struct WaitForUser
        : public BaseState // needs 2 sub states, retracting, and unretracting, and waiting
    { // wait for user needs to unretract when transitioning to wait for sync via NextPassEvent
        struct Waiting : public BaseState
        {
            struct NextPassEvent : public BaseEvent
            {
            };

            struct ReturnToStartEvent : public BaseEvent
            {
            };

            void OnEvent(const NextPassEvent&);
            void OnEvent(const ReturnToStartEvent&);
        };
    };

    struct TurningPass : public BaseState
    {
        struct Unretracting : public BaseState
        {
            void OnEvent(const MoveDoneEvent&);
        };

        struct WaitForSync : public BaseState
        {
            struct InSyncEvent : public BaseEvent
            {
            };
            void OnEvent(const InSyncEvent&);
        };

        struct Moving : public BaseState
        {
            void OnEvent(const MoveDoneEvent&);

            struct Retracting : public BaseState
            {
                void OnEvent(const MoveDoneEvent&);
            };

            void OnEvent(const StopEvent&);
        };

        // void OnEvent(const EStopEvent&); //this might be able to bubble up to the parent
    };

    struct ReturnToStart : public BaseState
    {
        struct Retracting : public BaseState
        {
            void OnEvent(const MoveDoneEvent&);
        };

        struct MovingToStart : public BaseState
        {
            void OnEvent(const MoveDoneEvent&); // Transition back to WaitForUser::Waiting
        };

        void OnEvent(const MoveDoneEvent&);
    };

    void OnEvent(const ExitEvent&);
    void OnEvent(const EStopEvent&);
    void OnEvent(const SetSettingsEvent&);

private:
    bool myRequiresSync = false; // false for turning modes, true for threading modes
    bool myForwardPass = true;   // true for to take a pass towards the destination, false for
                                 // towards the start. for reversing the cut direction without
                                 // redefining the start and end positions
    int32_t myDestinationPosition = 0;
    int32_t myStartPostion = 0;
    int32_t myFeedRate = 0;  // in distance per spindle rev
    int32_t myRapidRate = 0; // in distance per second
};