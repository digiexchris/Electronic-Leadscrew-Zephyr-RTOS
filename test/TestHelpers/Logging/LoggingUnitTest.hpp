
#include "Logging/Logger.hpp"
#include "etl_profile.h"

class LoggerBaseTest {
protected:
    LoggerBaseTest() {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }

    ~LoggerBaseTest() {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }
};