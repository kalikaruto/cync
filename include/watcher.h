#ifndef WATCHER_H
#define WATCHER_H

#include <string>
#include <functional>
#include <thread>
#include <atomic>

class Watcher {
public:
    // Callback takes the new clipboard content
    using ClipboardChangeCallback = std::function<void(const std::string&)>;

    Watcher();
    ~Watcher();

    // Start watching in a background thread.
    void start(ClipboardChangeCallback callback);

    // Stop watching.
    void stop();

private:
    void watchLoop();

    ClipboardChangeCallback m_callback;
    std::atomic<bool> m_running;
    std::thread m_thread;
};

#endif // WATCHER_H
