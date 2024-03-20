#pragma once

#include <etl/error_handler.h>
#include "Logging/Logger.hpp"

struct ErrorLog {
    void member_function(const etl::exception e) {
        ELSF_LOG_ERROR("%s:%s| %s", e.file_name(), e.line_number() ,e.what());
    }
};