#pragma once

#include <catch2/catch_all.hpp>
#include <catch2/trompeloeil.hpp>
#include <trompeloeil/mock.hpp>
#include <etl/string.h>
#include <cstdio>
#include <cstdarg> // For va_list, va_start, va_end
#include <string>
#include "Logging/Logger.hpp"
#include <fmt/core.h>

namespace Mocks::Logging  {

class MockLogBackend : public ILogBackend
{
public:
    MAKE_CONST_MOCK1(Info, void (etl::string<256> message));
    MAKE_CONST_MOCK1(Warn, void (etl::string<256> message));
    MAKE_CONST_MOCK1(Error, void (etl::string<256> message));
    explicit MockLogBackend(uint32_t id = 0) : uniqueId(id) {}



    uint32_t uniqueId; // Make sure uniqueId is public if you need to access it outside the class

private:
};

} // namespace Mocks::Logging
