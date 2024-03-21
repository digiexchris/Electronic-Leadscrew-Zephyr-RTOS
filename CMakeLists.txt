cmake_minimum_required(VERSION 3.13.1)
# set (BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
# set (DTC_OVERLAY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ELS.ovelay")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CONFIG_LIB_CPLUSPLUS ON)
set(CONFIG_NEWLIB_LIBC ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(NO_BUILD_TYPE_WARNING TRUE)
if(CONFIG_ZTEST)
set(BOARD native_sim)
endif()
set(QPCPP ${CMAKE_CURRENT_SOURCE_DIR}/qpcpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Zephyr stuff
set(ZEPHYR_EXTRA_MODULES ${QPCPP})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

#include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(app LANGUAGES C CXX ASM)

FILE(GLOB_RECURSE app_sources 
#main app
./src/*.c*
#tests
# ./test/*.c*
)

if(CONFIG_ZTEST)
    set(NO_BUILD_TYPE_WARNING TRUE)
    add_compile_definitions(CONFIG_SPINDLE_ENCODER_TYPE_TEST)

    # include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
    # project(app LANGUAGES C CXX ASM)

    FILE(GLOB test_sources ./*/*.c*)
    include_directories(./test/)
    
endif()

zephyr_include_directories(
 ${QPCPP}/include
 ${QPCPP}/zephyr
 ./src
)



# option to turn QSPY software tracing ON or OFF
# NOTE: Typically specified on command-line, e.g.:
# west build -b <board> -- -DQSPY=ON
#
option(QSPY "QSPY software tracing" OFF)

include_directories(src)
target_sources(app PRIVATE ${app_sources} ${test_sources})



