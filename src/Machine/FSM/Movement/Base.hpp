#pragma once

#include "../sml.hpp"

#include "CommonEvents.hpp"

class BaseState
{
public:
    template <class TEvent>
    void OnEvent(const TEvent&);

    virtual void Tick();
};

class Action
{
public:
    template <class TEvent>
    void operator()(BaseState& sm, const TEvent& event)
    {
        sm.OnEvent(event);
    }
};
