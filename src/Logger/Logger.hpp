/**
 * @file ILogger.hpp
 * @brief This file defines the interface for the logger.
 * Override the log backend with a custom implementation,
 * and instantiate the Log with that backend.
 * 
 * An example implementation is in test/TestHelpers/Logging/TestLogBackend.hpp
 * 
 * If you wanted to write a logger for the ESP32, you could replace the calls to
 * PrintLog() in TestLogBackend::Log(), TestLogBackend::Info(), etc...
 * with the appropriate ESP32 logging functions, like ESP_LOGI, ESP_LOGE, etc...
 * 
 * See test/setup.cpp for an example of how to set the backend.
*/

#pragma once

#include "boost/assert/source_location.hpp"
#include <config.hpp>
#include <stdarg.h>
#include <fmt/core.h>
#include <boost/static_string.hpp>
#include <boost/assert.hpp>
#include <exception>

using LogCallback = std::function<void (std::string_view)>;

constexpr uint16_t ELSF_LOG_MAX_MESSAGE_LENGTH = 256;

#define ELSF_LOG_INIT(BackendPTR) LogSingleton::create(std::move(BackendPTR))
#define ELSF_LOG_INFO(...) LogSingleton::instance().Info(__VA_ARGS__)
#define ELSF_LOG_WARN(...) LogSingleton::instance().Warn(__VA_ARGS__)
#define ELSF_LOG_ERROR(...) LogSingleton::instance().Error(__VA_ARGS__)

#define LOGGER_INIT_EXCEPTION(reason) LoggerInitException((reason), __FILE__, __LINE__)

class LoggerInitException : public std::exception
{


};

class ILogBackend
{
public:
    //NOTE: any taking in of formatting params happens in the Logger.
    virtual void Info(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const = 0;

    virtual void Warn(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const = 0;
    
    virtual void Error(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const = 0;

    virtual ~ILogBackend() = default;
    
};


class Logger
{
public:
    template<typename... Args>
    void Info(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    template<typename... Args>
    void Warn(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    template<typename... Args>
    void Error(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    void SetBackend(ILogBackend* aBackend) {
        BOOST_ASSERT_MSG(aBackend != nullptr, "Log not initialized, call ESP_LOG_INIT");
        myLogBackend.reset(aBackend);
    }

    ILogBackend* GetBackend() const {
        return myLogBackend.get();
    }

    explicit Logger(ILogBackend* aBackend) {
        SetBackend(aBackend);
    }
protected:

    template <typename... Args>
    boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> ApplyFormat(const boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH>& message, Args&&... args) const;

private:
    std::unique_ptr<ILogBackend> myLogBackend;
};

//using LogSingleton = std::singleton<Logger>;


template<typename... Args>
void Logger::Info(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    myLogBackend->Info(ApplyFormat(message, std::forward<Args>(args)...));
}

template<typename... Args>
void Logger::Warn(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    myLogBackend->Warn(ApplyFormat(message, std::forward<Args>(args)...));
}

template<typename... Args>
void Logger::Error(boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    myLogBackend->Error(ApplyFormat(message, std::forward<Args>(args)...));
}

template <typename... Args>
boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH> Logger::ApplyFormat(const boost::static_string<ELSF_LOG_MAX_MESSAGE_LENGTH>& message, Args&&... args) const
{
    return fmt::format(message.c_str(), std::forward<Args>(args)...).c_str();
}
