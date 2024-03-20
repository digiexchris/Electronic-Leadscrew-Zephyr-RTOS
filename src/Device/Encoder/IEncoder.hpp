#pragma once

#include "Device/State/Position.hpp"

namespace Device::Encoder
{

class IEncoder : public State::Position
{
    using State::Position::Position;
};

} // namespace Device