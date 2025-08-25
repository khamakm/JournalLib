#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <thread>

#include "JournalLib.hpp"
#include "JournalWorker.hpp"

class InputCore {
    private:
        std::string datetime;
        std::string level;
        std::string message;
        JournalCore& journal;
    public: 
        InputCore(JournalCore& journal);

        void set_datetime(std::string datetime);
        void set_level(std::string level);
        void set_message(std::string message);

        std::string get_datetime();
        std::string get_level();
        std::string get_message();

        void clear_input();
        std::string get_cur_datetime();
        void input_parce(std::string input);
        static bool is_correct_message(std::string str);
};
