#include "JournalLib.hpp"

JournalCore::JournalCore(std::string file_name, std::string def_level)
    : file_name(file_name), def_level(def_level) {}

void JournalCore::set_def_level(std::string new_def_level) {
    def_level = new_def_level;
    std::cout << "Changed level to " << def_level << "\n> " << std::flush;
}

std::string JournalCore::get_def_level() {return def_level;}

void JournalCore::write_to_journal(std::string datetime, std::string level, std::string message) {
    if (JournalCore::level_to_int(level) < JournalCore::level_to_int(def_level)) return;
    
    std::ofstream fout(file_name, std::ios_base::out | std::ios_base::app);

    if (!fout.is_open()) {
        std::cerr << "ERROR: Fail open file." << std::endl;
        return;
    }
    
    fout << datetime << "\t" << level << "\t" << message << std::endl;
    fout.close();
    std::cout << std::endl <<"Complete write to journal.\n> " << std::flush;
}

std::string JournalCore::int_to_level(int level) {
    if (level == 1) return LEVEL_1;
    if (level == 2) return LEVEL_2;
    if (level == 3) return LEVEL_3;
    return "ERROR";
}

int JournalCore::level_to_int(std::string level) {
    if (level == LEVEL_1) return 1;
    if (level == LEVEL_2) return 2;
    if (level == LEVEL_3) return 3;
    return 0;
}

bool JournalCore::is_correct_level(std::string level) {
    if (level == LEVEL_1 || level == LEVEL_2 || level == LEVEL_3) return true;
    return false;
}

bool JournalCore::is_correct_file(std::string path) {
    if (path.find(".txt") == path.size()-4) {
        std::ofstream fout(path, std::ios_base::out | std::ios_base::app);
        if (fout.is_open()) {
            fout.close();
            return true;
        }
    }
    return false;
}