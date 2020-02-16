cmake_minimum_required(VERSION 3.10)
project(trading-bot-binance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wfatal-errors -Wpedantic -Wextra -Wmissing-include-dirs -Wconversion -Wsign-conversion -pthread")
add_compile_options(-Wall -Werror -Wfatal-errors -Wpedantic -Wextra -Wmissing-include-dirs -Wconversion -Wsign-conversion -pthread)

#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -march=native -g")

find_package(Boost 1.71 REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

include_directories(config)
include_directories(src)
include_directories(SYSTEM src/common/external)

add_subdirectory(src/binance/fapi)
add_subdirectory(src/binance/fapi/tests)
add_subdirectory(src/common/util)

