#include "Encoder/IEncoder.hpp"
#include <stdlib.h>
#include <etl/absolute.h>
#include <etl/atomic.h>

Encoder::Encoder() {
    myStatus = {0, false, 0, 0, 0, false, 0, 0};
}

uint16_t Encoder::GetCountPeriod() {
    Status status = myStatus.load();
    uint16_t timeDifference = status.timestamp - status.lastTimestamp;
    int32_t countDifference = etl::absolute(static_cast<int32_t>(status.count) - static_cast<int32_t>(status.lastCount));

    // Check if countDifference is not zero to avoid division by zero
    if (countDifference != 0) {
        uint16_t averageTimeBetweenCounts = timeDifference / countDifference;
        return averageTimeBetweenCounts;
    } else {
        return 0;
    }
}

Encoder::Status Encoder::GetMotionParams() {
    return myStatus.load();
}