#pragma once

// #include "Logging/Logger.hpp"
// #include "TestHelpers/Logging/TestLogBackend.hpp"

#include <gtest/gtest.h>

struct DefaultUnitTest : public ::testing::Test
{
public:
    // TestLogBackend* testLogBackend;

    // DefaultUnitTest() {
    //     if(LogSingleton::is_valid()) {
    //         LogSingleton::destroy();
    //     }
    //     testLogBackend = new TestLogBackend();
    //     ELSF_LOG_INIT(testLogBackend);
    // }
    // ~DefaultUnitTest() {
    //     if(LogSingleton::is_valid()) {
    //         LogSingleton::destroy();
    //     }
    // }
};