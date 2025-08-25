#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#define LEVEL_1 "LOW"
#define LEVEL_2 "MEDIUM"
#define LEVEL_3 "HIGHT"
#define DEF_LEVEL LEVEL_1
#define DEF_FILE_NAME "journal.txt"

enum error {
    ERROR_WRONG_LEVEL
};

class JournalCore {
    private:
        std::string file_name;
        std::string def_level;
        std::string time_receipt;
    
    public:
        JournalCore(std::string new_file_name, std::string new_def_level);
        
        void set_def_level(std::string new_def_level);

        std::string get_def_level();
        
        void write_to_journal(std::string datetime, std::string level, std::string message);
        std::string int_to_level(int level);
        static int level_to_int(std::string level);
        static bool is_correct_level(std::string level);
        static bool is_correct_file(std::string path);
};