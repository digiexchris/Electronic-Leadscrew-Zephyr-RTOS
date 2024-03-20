#pragma once

struct BaseEvent
{
};

struct ExitEvent : public BaseEvent
{
};

struct StopEvent : public BaseEvent
{
};

struct MoveDoneEvent : public BaseEvent
{
};

struct EStopEvent : public BaseEvent
{
};
