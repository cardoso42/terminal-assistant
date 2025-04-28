#pragma once

#include <string>
#include <string_view>

class CommandExecutor
{
public:
    static bool execute(const std::string &command);
    static bool prompt_and_execute(const std::string &command);
};
