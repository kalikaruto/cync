#include "watcher.h"
#include "clipboard.h" // We need this to get the clipboard content
#include <chrono>
#include <iostream>

Watcher::Watcher() : m_running(false) {}

Watcher::~Watcher() {
    stop();
}

void Watcher::start(ClipboardChangeCallback callback) {
    if (m_running.load()) {
        return;
    }
    m_callback = callback;
    m_running = true;
    m_thread = std::thread(&Watcher::watchLoop, this);
}

void Watcher::stop() {
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void Watcher::watchLoop() {
    Clipboard clipboard;
    std::string lastContent = clipboard.get();

    while (m_running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (!m_running) break;

        std::string newContent = clipboard.get();
        if (newContent != lastContent) {
            lastContent = newContent;
            if (m_callback) {
                m_callback(lastContent);
            }
        }
    }
}
