cmake_minimum_required(VERSION 3.10)

project(tic-tac-toe)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options(/W4 /WX)
    # Do not specify /O2 because there are Debug/Release modes.
else ()
    if (NOT DEFINED CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)  # Add debug information
    endif (NOT DEFINED CMAKE_BUILD_TYPE)

    add_compile_options(-Wall -Wextra -Werror -O2)
    if (UNIX AND NOT DEFINED CMAKE_CXX_FLAGS)  # Do not add if -DCMAKE_CXX_FLAGS is passed
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address -lncurses)
    endif (UNIX AND NOT DEFINED CMAKE_CXX_FLAGS)
endif (MSVC)

add_subdirectory(mytest)  # Add only after all compilation options are specified.

include_directories(include)  # Add only after 'mytest' is included, so it's independent.

add_library(view_common OBJECT src/view_common.cpp)
add_library(common OBJECT src/game.cpp)
add_library(Loud OBJECT src/view_cli_loud.cpp)
add_library(Silent OBJECT src/view_cli_silent.cpp)
add_library(Interactive src/view_interactive.cpp)

add_executable(tic-tac-toe-loud src/main.cpp)
target_link_libraries(tic-tac-toe-loud common Loud view_common)

add_executable(tic-tac-toe-silent src/main.cpp)
target_link_libraries(tic-tac-toe-silent common Silent view_common)

add_executable(tic-tac-toe-test mytest/src/mytest_main.cpp
        src/game_test.cpp)
target_link_libraries(tic-tac-toe-test common mytest-main Loud view_common)

add_library(new_common src/game.cpp)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_library(view-interactive src/view_interactive.cpp)
add_executable(tic-tac-toe-interactive src/main.cpp)
target_link_libraries(tic-tac-toe-interactive new_common view-interactive ${CURSES_LIBRARIES})