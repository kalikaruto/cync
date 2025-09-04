cmake_minimum_required(VERSION 3.18)
project(Cync VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Find all our source files
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
# Exclude main.cpp from the library sources, as it belongs in the executable
list(FILTER SOURCES EXCLUDE REGEX ".*/main.cpp$")


# --- Core Library ---
# By creating a library, we can share code between our main program and our tests.
add_library(cync_lib ${SOURCES})

# The PUBLIC keyword here means that any target that links to cync_lib
# will also get these compile definitions.
target_compile_definitions(cync_lib PUBLIC -DUSE_WAYLAND)


# --- Main Executable ---
# This just contains the main function and links to our library for the real logic.
add_executable(cync src/main.cpp)
target_link_libraries(cync PRIVATE cync_lib)


# --- Custom Run Target ---
add_custom_target(run
    COMMAND cync
    DEPENDS cync
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)


# --- Testing ---
# This section enables testing and includes the 'tests' directory,
# where we will configure and define our test cases.
enable_testing()
add_subdirectory(tests)