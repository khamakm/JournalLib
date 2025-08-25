#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "JournalWorker.hpp"
#include "JournalLib.hpp"
#include "inputCore.hpp"

int main(int argc, char* argv[]) {
    std::string file_name;
    while (true) {
        std::cout << "Set journal file name (*.txt): ";
        std::cin >> file_name;

        if (file_name == "exit") exit(0);
        if (JournalCore::is_correct_file(file_name)) break;
        std::cout << "Wrong type of the file." << std::endl;
    }

    std::string def_level;
    while (true) {
        std::cout <<    "Set importance level of the message\n"
                        "by default (\"LOW\", \"MEDIUM\", \"HIGHT\"): ";
        std::cin >> def_level;
        
        if (def_level == "exit") exit(0);
        if (JournalCore::is_correct_level(def_level)) break;
        std::cout << "Wrong importance level." << std::endl;
    }

    JournalCore journal = JournalCore(file_name, def_level);
    InputCore inputcore = InputCore(journal);
    JournalWorker journal_worker = JournalWorker(journal);

    inputcore.input_parce("help");

    while (true) {
        std::cout << "\n> ";
        std::string input = "";
        std::getline(std::cin, input);
        inputcore.input_parce(input);

        if (inputcore.get_level() == "") continue;
        journal_worker.add_task(inputcore.get_datetime(), inputcore.get_level(), inputcore.get_message());
        inputcore.clear_input();
    }
}
