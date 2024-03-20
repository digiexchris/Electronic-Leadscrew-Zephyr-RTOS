#include "Position.hpp"
#include <cmath>

namespace State
{

Position::Position(float myScaleFactor) : myScaleFactor(myScaleFactor) {}

void Position::Update() { Set(UpdateMotionParams()); };

void Position::SetScaleFactor(float aScaleFactor) { myScaleFactor = aScaleFactor; }

void Position::Set(PositionParams aParams)
{

    myLastRawCount = myRawCount;
    myLastDirection = myDirection;
    myLastTimestamp = myTimestamp;

    // Directly apply the carry to the incoming raw count.
    // myCarry is now assumed to be a float or double to retain necessary precision.
    float newRawCountWithCarry = static_cast<float>(aParams.count) + myCarry;
    myRawCount = static_cast<int32_t>(newRawCountWithCarry);

    myDirection = aParams.direction;
    myTimestamp = aParams.timestamp;

    // Perform the scaling with a carry-inclusive new raw count.
    float newScaledCount = newRawCountWithCarry * myScaleFactor;
    myCount = static_cast<int32_t>(newScaledCount);

    // Computing carry for the next cycle.
    // Subtracts the matching floor integer version of itself (representing myCount)
    // and does not readjust with myScaleFactor - carry is kept as the unscaled extra
    myCarry = newScaledCount - static_cast<float>(myCount);
}

int32_t Position::GetPosition() const { return myCount; }

bool Position::GetDirection() const { return myDirection; }

uint32_t Position::GetTimestamp() const { return myTimestamp; }

bool Position::operator>(const Position& aPosition) const
{
    return GetPosition() > aPosition.GetPosition();
}

bool Position::operator<(const Position& aPosition) const
{
    return GetPosition() < aPosition.GetPosition();
}

bool Position::operator==(const Position& aPosition) const
{
    return GetPosition() == aPosition.GetPosition();
}

int32_t Position::operator-(const Position& aPosition) const
{
    return GetPosition() - aPosition.GetPosition();
}

int32_t Position::operator+(const Position& aPosition) const
{
    return GetPosition() + aPosition.GetPosition();
}

float Position::GetCountPeriod() const
{
    uint32_t timeDifference = myTimestamp - myLastTimestamp;
    float countDifference = std::abs(static_cast<float>(myRawCount) * myScaleFactor) -
                            static_cast<float>(myLastRawCount) * myScaleFactor;

    // Check if countDifference is not zero to avoid division by zero
    if (countDifference != 0)
    {
        float averageTimeBetweenCounts = static_cast<float>(timeDifference) / countDifference;
        return averageTimeBetweenCounts;
    }
    else
    {
        return 0;
    }
}

int32_t Position::Diff(const Position& aPosition) const
{
    return GetPosition() - aPosition.GetPosition();
}

} // namespace State