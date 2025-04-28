#include "api_client.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "json.hpp"

using json = nlohmann::json;

ApiClient::ApiClient() : api_key_(get_api_key()) {}

std::string ApiClient::get_response(const std::string_view command) const
{
    validate_command(command);
    const std::string payload = create_payload(command);

    const std::vector<std::string> headers = {"Content-Type: application/json",
                                              "Authorization: Bearer " + api_key_};

    std::string response = CurlClient::post(API_URL, payload, headers);

    try
    {
        json response_json = json::parse(response);
        return response_json["choices"][0]["message"]["content"].get<std::string>();
    }
    catch (const json::exception &e)
    {
        throw std::runtime_error("Failed to parse API response: " + std::string(e.what()));
    }
}

std::string ApiClient::get_api_key()
{
    if (const char *env_key = std::getenv("DEEPSEEK_API_KEY"))
    {
        return {env_key};
    }

    if (std::filesystem::path config_path = std::filesystem::path(std::getenv("HOME")) / ".config" /
                                            "terminal-assistant" / "api_key";
        std::filesystem::exists(config_path))
    {
        if (std::ifstream file(config_path); file.is_open())
        {
            std::string key;
            std::getline(file, key);
            return key;
        }
    }

    throw std::runtime_error("API key not found. Please set DEEPSEEK_API_KEY environment variable "
                             "or create ~/.config/terminal-assistant/api_key file");
}

std::string ApiClient::create_payload(const std::string_view command)
{
    const json payload = {{"model", MODEL},
                          {"messages",
                           {{{"role", "system"}, {"content", SYSTEM_PROMPT}},
                            {{"role", "user"}, {"content", std::string(command)}}}},
                          {"temperature", TEMPERATURE},
                          {"max_tokens", MAX_RESPONSE_LENGTH}};
    return payload.dump();
}

void ApiClient::validate_command(const std::string_view command)
{
    if (command.empty())
    {
        throw std::invalid_argument("Command cannot be empty");
    }

    if (command.length() > MAX_COMMAND_LENGTH)
    {
        throw std::invalid_argument("Command exceeds maximum length of " +
                                    std::to_string(MAX_COMMAND_LENGTH) + " characters");
    }
}
