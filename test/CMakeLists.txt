cmake_minimum_required(VERSION 3.13.1)
set(BOARD qemu_cortex_m3 )
find_package(zephyr)
project(app)
target_sources(app PRIVATE Encoder/test_encoder.cpp)

# Assuming your ETL library is at '../lib/etl'
# Specify the binary directory for the external project
set(ETL_BINARY_DIR ${CMAKE_BINARY_DIR}/build/etl_build)

# Add the ETL library as a subdirectory
add_subdirectory(../lib/etl ${ETL_BINARY_DIR})
target_link_libraries(app PUBLIC etl)

# Add the code under test source files
file(GLOB APP_SOURCES "../src/Encoder/*.cpp")
target_sources(app PRIVATE ${APP_SOURCES})
target_include_directories(app PRIVATE ../include/)