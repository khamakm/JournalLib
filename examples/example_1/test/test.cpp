#include <condition_variable>
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

#include "JournalWorker.hpp"
#include "JournalLib.hpp"
#include "inputCore.hpp"

#define TEST_INPUT_FILE "./examples/example_1/test/test_input.txt"

int main(int argc, char* argv[]) {
    
    std::ifstream test_in(TEST_INPUT_FILE);
    if (!test_in.is_open()) std::cerr << "Can't open test input file." << std::endl;

    std::string file_name;
    while (true) {
        std::cout << "\nSet journal file name (*.txt): ";
        std::getline(test_in, file_name); 

        std::cout << file_name << std::endl;

        if (file_name == "exit") exit(0);
        if (JournalCore::is_correct_file(file_name)) break;
        std::cout << "\nWrong type of the file." << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::string def_level;
    while (true) {
        std::cout <<    "\nSet importance level of the message\n"
                        "by default (\"LOW\", \"MEDIUM\", \"HIGHT\"): ";
        std::getline(test_in, def_level); 

        std::cout << def_level << std::endl;

        if (def_level == "exit") exit(0);
        if (JournalCore::is_correct_level(def_level)) break;
        std::cout << "\nWrong importance level." << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    JournalCore journal = JournalCore(file_name, def_level);
    InputCore inputcore = InputCore(journal);
    JournalWorker journal_worker = JournalWorker(journal);

    while (true) {
        std::cout << "\n> ";
        std::string input = "";
        std::getline(test_in, input);

        std::cout << input << std::endl;
        
        inputcore.input_parce(input);

        if (inputcore.get_level() == "") continue;
        journal_worker.add_task(inputcore.get_datetime(), inputcore.get_level(), inputcore.get_message());
        inputcore.clear_input();
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}