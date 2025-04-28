#include <iostream>
#include <string>
#include <string_view>
#include "api_client.hpp"
#include "command_executor.hpp"

int main(const int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <command>" << std::endl;
        std::cerr << "The command cannot be empty and must be at most 1000 characters long."
                  << std::endl;
        return 1;
    }

    try
    {
        const ApiClient client;
        const std::string_view command = argv[1];
        const std::string answer = client.get_response(command);
        std::cout << answer << std::endl;

        if (!CommandExecutor::prompt_and_execute(answer))
        {
            std::cerr << "Error executing command" << std::endl;
            return 1;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Input error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
