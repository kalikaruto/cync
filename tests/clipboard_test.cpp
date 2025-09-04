#include "gtest/gtest.h"
#include "clipboard.h"
#include <thread>   // For std::this_thread
#include <chrono>   // For std::chrono

// This test case checks the basic functionality of the Clipboard class.
// NOTE: This is an integration test because it interacts with the live
// system clipboard by calling wl-copy and wl-paste.


// TEST_F is used when you are using a test fixture.
// It defines a test named 'SetAndGet' within the 'ClipboardTest' suite.
TEST(Clipboard, SetAndGet) {
    const std::string test_string = "Hello from the Cync test suite!";
    
    // Set the clipboard content
    Clipboard::set(test_string);

    // Add a small delay to give the clipboard manager time to process the change.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Get the clipboard content back
    std::string result = Clipboard::get();

    // Assert that the retrieved content matches what we set.
    // We use ASSERT_EQ, which is a fatal assertion. If it fails,
    // the test stops immediately.
    ASSERT_EQ(result, test_string);
}

// Another test to ensure setting an empty string works.
TEST(Clipboard, HandlesEmptyString) {
    const std::string test_string = "";
    Clipboard::set(test_string);

    // Add a small delay here as well.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::string result = Clipboard::get();
    ASSERT_EQ(result, test_string);
}