cmake_minimum_required(VERSION 3.22.1)
project(Solution)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_executable(Solution
                main.cc
                )

# C++ Requests integration
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.10.5)
FetchContent_MakeAvailable(cpr)
target_link_libraries(Solution PRIVATE cpr::cpr)

# Nlohmann JSON integration
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(Solution PRIVATE nlohmann_json::nlohmann_json)
