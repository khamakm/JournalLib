#include "JournalWorker.hpp"

JournalWorker::JournalWorker(JournalCore& journal) : running(true), journal(journal) {
    worker_thread = std::thread(&JournalWorker::process_tasks, this);
}

JournalWorker::~JournalWorker() {
    running = false;
    condition.notify_one();
    if (worker_thread.joinable()) worker_thread.join();
}

void JournalWorker::add_task(std::string datetime, std::string level, std::string message) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    tasks.push({datetime, level, message});
    condition.notify_one();
}

void JournalWorker::process_tasks() {
    while (running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        condition.wait(lock, [this]() { return !tasks.empty() || !running; });

        while (!tasks.empty()) {
            JournalTask task = tasks.front();
            tasks.pop();
            lock.unlock();

            try {
                if (task.datetime == "") journal.set_def_level(task.level);
                else journal.write_to_journal(task.datetime, task.level, task.message);
            } catch (const std::exception& excp) {
                std::cerr << "Failed to write to journal: " << excp.what() << std::endl;
            }

            lock.lock();
        }
    }
}
