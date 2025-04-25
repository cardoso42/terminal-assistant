#include "command_executor.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

bool CommandExecutor::execute(const std::string& command) {    
    // Use bash -i to run in interactive mode, which preserves colors
    std::string full_command = "bash -i -c '" + command + "'";
    int result = std::system(full_command.c_str());
    return result == 0;
}

bool CommandExecutor::prompt_and_execute(const std::string& command) {
    std::cout << "Do you want to execute it? (Y/n): ";
    std::string choice;
    std::getline(std::cin, choice);
    
    // If empty input (just Enter) or starts with Y/y, execute
    if (choice.empty() || choice[0] == 'Y' || choice[0] == 'y') {
        return execute(command);
    }
    
    return true; // Return true if user chose not to execute (N/n)
}
