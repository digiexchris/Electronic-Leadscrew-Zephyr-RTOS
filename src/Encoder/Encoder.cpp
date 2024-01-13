#include "Encoder/IEncoder.hpp"
#include <stdlib.h>

Encoder::Encoder() {
    myCount = 0;
    myLastCount = 0;
    myCountUpdateTime = 0;
    myLastCountUpdateTime = 0;
}

uint16_t Encoder::GetCountPeriod() {
    uint16_t timeDifference = myCountUpdateTime - myLastCountUpdateTime;
    int32_t countDifference = std::abs(static_cast<int32_t>(myCount) - static_cast<int32_t>(myLastCount));

    // Check if countDifference is not zero to avoid division by zero
    if (countDifference != 0) {
        uint16_t averageTimeBetweenCounts = timeDifference / countDifference;
        return averageTimeBetweenCounts;
    } else {
        return 0;
    }
}

uint32_t Encoder::GetPosition() {
    return myCount;
}