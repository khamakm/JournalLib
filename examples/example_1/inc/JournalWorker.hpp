#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "JournalLib.hpp"

struct JournalTask {
    std::string datetime;
    std::string level;
    std::string message;
};

class JournalWorker {
    private:
        std::queue<JournalTask> tasks;
        std::mutex queue_mutex;
        std::condition_variable condition;
        std::atomic<bool> running;
        std::thread worker_thread;
        JournalCore& journal;
        void process_tasks();
    public:
        JournalWorker(JournalCore& journal);
        ~JournalWorker();
        void add_task(std::string datetime, std::string level, std::string message);
};