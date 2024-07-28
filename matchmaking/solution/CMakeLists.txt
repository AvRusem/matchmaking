cmake_minimum_required(VERSION 3.22.1)
project(Solution)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    Solution

    main.cc
    user.cc
    uuid_generator.cc
    solver.cc
    request_manager.cc
    functions.cc
    solver_roles_greedy.cc
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

option(BUILD_LOCAL "Build unit tests. Run with ctest. Change URL" OFF)

if(BUILD_LOCAL)
    target_compile_definitions(Solution PRIVATE "BUILD_LOCAL")

    # GoogleTest integration
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    FetchContent_MakeAvailable(googletest)

    # Enable unit tests
    enable_testing()

    add_executable(
        Tests

        role_test.cc

        user_test.cc
        user.cc

        team_test.cc

        match_test.cc

        solver_test.cc
        solver.cc
        uuid_generator.cc

        functions_test.cc
        functions.cc
    )

    target_link_libraries(
        Tests
        GTest::gtest_main
        cpr::cpr
        nlohmann_json::nlohmann_json
    )

    include(GoogleTest)
    gtest_discover_tests(Tests)
endif()
