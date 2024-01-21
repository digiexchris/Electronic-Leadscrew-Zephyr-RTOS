#pragma once
//based on #include <etl/profiles/armv7.h>
#define ETL_TARGET_DEVICE_ARM
#define ETL_TARGET_OS_NONE
#define ETL_COMPILER_GCC
#define ETL_CPP11_SUPPORTED 1
#define ETL_CPP14_SUPPORTED 0
#define ETL_CPP17_SUPPORTED 0
#define ETL_NO_NULLPTR_SUPPORT 0
#define ETL_NO_LARGE_CHAR_SUPPORT 0
#define ETL_NO_STL 1
#define ETL_CPP11_TYPE_TRAITS_IS_TRIVIAL_SUPPORTED 1

#define ETL_THROW_EXCEPTIONS
#define ETL_VERBOSE_ERRORS

// #if defined(_MSC_VER)
//   #include "etl/profiles/msvc_x86.h"
// #elif defined(__GNUC__)
//   #include "etl/profiles/gcc_generic.h"
// #endif