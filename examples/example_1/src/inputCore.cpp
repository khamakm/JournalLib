#include "inputCore.hpp"

InputCore::InputCore(JournalCore& journal) : journal(journal) {}

void InputCore::set_datetime(std::string datetime) {this->datetime = datetime;}
void InputCore::set_level(std::string level) {this->level = level;}
void InputCore::set_message(std::string message) {this->message = message;}

std::string InputCore::get_datetime() {return this->datetime;}
std::string InputCore::get_level() {return this->level;}
std::string InputCore::get_message() {return this->message;}

void InputCore::clear_input() {
    set_datetime("");
    set_level("");
    set_message("");
}

void InputCore::input_parce(std::string input) {
    if (input.empty()) return;
    
    else if (input.rfind("setlevel ", 0) == 0) {
        std::string def_level = input.substr(9);
        if (!JournalCore::is_correct_level(def_level)) 
            std::cout << "\nWrong importance level. Type \"help\" for more information." << std::endl ;
        set_level(def_level);
    }
    else if (input == "exit") exit(0);
    else if (input == "help") {
        std::cout   << "Usage:\n"
                    << "    message <LEVEL> \"<some_message>\"        Save message to journal.\n"
                    << "    setlevel <LEVEL>                        Set the importance level of\n"
                    << "                                            the message by default.\n"
                    << "    help                                    Show help.\n"
                    << "    exit                                    Exit from program.\n"
                    << "    <LEVEL>: \"LOW\", \"MEDIUM\", \"HIGHT\"\n" 
                    << "    Example: message MEDIUM \"text\"\n"
                    << "             setlevel HIGHT \"text\"\n"
                    << "    For use default importance level:\n"
                    << "             message \"text\"" << std::endl;
    } 
    else if (input.rfind("message ", 0) == 0) {
        std::string options = input.substr(8);
        if (!InputCore::is_correct_message(options)) {
            std::cout << "\nWrong command structure. Type \"help\" for more information." << std::endl;
            return;
        }

        std::string level, message;
        if (options.find("\"") == 0) {
            level = journal.get_def_level();
            message = options.substr(1, options.length() - 2);
        }
        else {
            level = options.substr(0, options.find(" "));
            message = options.substr(level.size()+1);
            message = message.substr(1, message.length() - 2);
        } 

        set_datetime(get_cur_datetime());
        set_level(level);
        set_message(message);
    } 
    else std::cout << "\nCommand not found. Type \"help\" for more information" << std::endl;
}

std::string InputCore::get_cur_datetime() {
    std::string datetime;

    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&time_now);

    std::stringstream ss;
    ss << std::put_time(&local_time, "%d.%m.%Y %H:%M:%S");

    return ss.str();
}

bool InputCore::is_correct_message(std::string str) {
    if (str.find_last_of("\"") == (str.size()-1)) {
        if (str.find("\"") == 0) return true;
        std::string level = str.substr(0, str.find(" "));
        if (JournalCore::is_correct_level(level)) return true;
    }
    return false;
}