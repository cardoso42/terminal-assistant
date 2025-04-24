#include <iostream>
#include <string>
#include <string_view>
#include "api_client.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command>" << std::endl;
        std::cerr << "The command cannot be empty and must be at most 1000 characters long." << std::endl;
        return 1;
    }

    try {
        ApiClient client;
        std::string_view command = argv[1];
        std::string answer = client.get_response(command);
        std::cout << answer << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
