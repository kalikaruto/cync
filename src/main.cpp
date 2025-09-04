#include "watcher.h"
#include <iostream>
#include <chrono>
#include <thread>

// This function will be called by the watcher when the clipboard changes
void onClipboardChange(const std::string& content) {
    std::cout << "\n--- Clipboard Changed! ---" << std::endl;
    std::cout << content << std::endl;
    std::cout << "--------------------------" << std::endl;
}

int main() {
    Watcher watcher;
    watcher.start(onClipboardChange);

    std::cout << "Clipboard watcher started. Monitoring for changes..." << std::endl;
    std::cout << "Try copying something to your clipboard." << std::endl;
    std::cout << "(Press Ctrl+C to exit)" << std::endl;

    // Keep the main thread alive to allow the watcher to run.
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    return 0;
}