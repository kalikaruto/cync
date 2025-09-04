# This CMake module helps manage external dependencies.
include(FetchContent)

# Declare the GoogleTest dependency. CMake will download it from GitHub.
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)

# This command makes the GoogleTest targets (like GTest::gtest_main) available for us to use.
FetchContent_MakeAvailable(googletest)


# --- Test Executable ---
# Create an executable that will contain our tests.
add_executable(cync_tests
    clipboard_test.cpp
)

# Link our test program against our cync_lib and GoogleTest.
# GTest::gtest_main provides a main() function for us, so we don't have to write one.
target_link_libraries(cync_tests PRIVATE cync_lib GTest::gtest_main)


# --- Custom Test Runner ---
# The standard 'ctest' runner fails in this environment because it sanitizes
# the environment too much for Wayland clients.
# Instead, we provide a custom target that runs the test executable directly.
add_custom_target(run-tests
    COMMAND cync_tests
    DEPENDS cync_tests
)