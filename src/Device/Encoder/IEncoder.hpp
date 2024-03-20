#pragma once

#include "State/Position.hpp"

namespace Device
{

class IEncoder : public State::Position
{
    using State::Position::Position;
};

} // namespace Device