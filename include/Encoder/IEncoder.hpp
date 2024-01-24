#pragma once
#ifndef IENCODER_HPP
#define IENCODER_HPP
#include <stdint.h>
#include <etl/atomic.h>
/**
 * @brief The Encoder class is an abstract base class for encoders.
 * 
 * It provides methods to get the position, update the encoder, and get the average time between counts.
 */
class Encoder {
public:
    struct Status {
        int32_t count;
        bool direction;
        uint32_t timestamp;
        uint16_t speed;
        uint32_t lastCount;
        bool lastDirection;
        uint32_t lastTimestamp;
        uint16_t lastSpeed;
    };

    Encoder();

    /**
     * @brief Gets the position, direction, speed, etc. of the encoder.
     * 
     * @note it's recommended to do as much as possible with a single read of this
     * since it's backed by std::atomic and is more expensive than reading individual
     * ints, but guarantees the timestamps, speed, and direction are consistent.
     * 
     * @return The position, direction, speed, etc. of the encoder as a Status struct.
     */
    Status GetMotionParams();

    /**
     * @brief Returns the average time between counts in milliseconds.
     * 
     * @return The average time between counts as a uint16_t value.
     * If the period is zero, the encoder has not moved since the last update.
     */
    virtual uint16_t GetCountPeriod() final;
    
    /**
     * @brief Updates the encoder.
     * 
     * This method should be called periodically by the update task to update the encoder's count.
     */
    virtual void Update() = 0;

protected:
    etl::atomic<Status> myStatus;   ///< The current and previous position, speed and direction of the encoder.
    
};

#endif // IENCODER_HPP