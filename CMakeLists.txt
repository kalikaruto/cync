cmake_minimum_required(VERSION 3.18)
project(Cync VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# --- Collect Sources ---
# Common sources from the utils directory
file(GLOB COMMON_SOURCES CONFIGURE_DEPENDS "src/utils/*.cpp")

# --- Detect platform and select platform-specific sources ---
if(UNIX AND NOT ANDROID)
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS "src/*_wl.cpp")
    set(CLIPBOARD_BACKEND "WAYLAND")
elseif(ANDROID)
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS "src/*_and.cpp")
    set(CLIPBOARD_BACKEND "ANDROID")
elseif(WIN32)
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS "src/*_win.cpp")
    set(CLIPBOARD_BACKEND "WINDOWS")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# --- Core Library ---
# Combine the common sources and the platform-specific sources
add_library(cync_lib ${COMMON_SOURCES} ${PLATFORM_SOURCES})
target_compile_definitions(cync_lib PUBLIC -DUSE_${CLIPBOARD_BACKEND})

# --- Link against required system packages ---
# Only Windows needs to link a specific library for its clipboard API.
# Wayland and Android backends work by calling external commands, so they don't need to link anything.
if(CLIPBOARD_BACKEND STREQUAL "WINDOWS")
    target_link_libraries(cync_lib PRIVATE user32) # Windows clipboard API
endif()

# --- Main Executable ---
add_executable(cync src/main.cpp)
target_link_libraries(cync PRIVATE cync_lib)

# --- Custom Run Target ---
add_custom_target(run
    COMMAND cync
    DEPENDS cync
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# --- Testing ---
enable_testing()
add_subdirectory(tests)
