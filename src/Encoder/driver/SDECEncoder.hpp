#pragma once
#include "IEncoder.hpp"

class SDECEncoder : public IEncoder {
public:
    SDECEncoder();
    uint32_t GetPosition() override;
    uint16_t GetCountPeriod() override;
}