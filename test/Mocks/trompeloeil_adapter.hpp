#pragma once

#include "trompeloeil.hpp"                   //** 2 **//

namespace trompeloeil
{
  template <>
  inline void reporter<specialized>::send(      //** 3 **//
    severity s,
    char const* file,
    unsigned long line,
    std::string const& msg)
  {
    auto f = line ? file : "[file/line unavailable]";
    if (s == severity::fatal)
    {
      ADD_FAIL_AT(f, line, msg);                //** 4 **//
    }
    else
    {
      ADD_FAIL_CHECK_AT(f, line, msg);          //** 4 **//
    }
  }
}