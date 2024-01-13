#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "driver/Encoder/IEncoder.hpp"

// Mock class for testing
class MockEncoder : public Encoder {
public:
    MOCK_METHOD0(GetCount, uint16_t());
    MOCK_METHOD0(GetCountUpdateTime, uint16_t());
};

// Test case for Encoder::GetCountPeriod()
TEST(EncoderTest, GetCountPeriodTest) {
    MockEncoder encoder;

    // Set up mock behavior
    EXPECT_CALL(encoder, GetCount()).WillOnce(::testing::Return(10));
    EXPECT_CALL(encoder, GetCountUpdateTime()).WillOnce(::testing::Return(100));
    EXPECT_CALL(encoder, GetCount()).WillOnce(::testing::Return(20));
    EXPECT_CALL(encoder, GetCountUpdateTime()).WillOnce(::testing::Return(200));

    // Call the function under test
    uint16_t result = encoder.GetCountPeriod();

    // Check the result
    EXPECT_EQ(result, 10); // Expected average time between counts is 10

    // Verify mock expectations
    ::testing::Mock::VerifyAndClearExpectations(&encoder);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}