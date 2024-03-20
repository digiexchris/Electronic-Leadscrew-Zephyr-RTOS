cmake_minimum_required(VERSION 3.13.1)
# set (BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
# set (DTC_OVERLAY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ELS.ovelay")
set(NO_BUILD_TYPE_WARNING TRUE)
set(BOARD native_sim)
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
./test/*.c*
./test/*.c*
)

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
target_sources(app PRIVATE ${app_sources})


