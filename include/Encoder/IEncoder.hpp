#pragma once
#include <cstdint>

/**
 * @brief The Encoder class is an abstract base class for encoders.
 * 
 * It provides methods to get the position, update the encoder, and get the average time between counts.
 */
class Encoder {
public:

    Encoder();

    /**
     * @brief Gets the current position of the encoder.
     * 
     * @return The current position as a uint32_t value.
     */
    virtual uint32_t GetPosition();

    /**
     * @brief Gets the direction of the encoder.
     * 
     * @return The direction of the encoder as a bool value.
     * True is up, false is down.
     */
    virtual bool GetDirection() = 0;

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
     * This method should be called periodically to update the encoder's count.
     */
    virtual void Update() = 0;

protected:
    uint32_t myCount;                   ///< The current count of the encoder.
    uint32_t myCountUpdateTime;         ///< The timestamp of the last count update.
    uint32_t myLastCount;               ///< The previous count of the encoder.
    uint32_t myLastCountUpdateTime;     ///< The timestamp of the previous count update.
};

