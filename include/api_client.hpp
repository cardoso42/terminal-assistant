#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "curl_client.hpp"

class ApiClient {
public:
    ApiClient();
    std::string get_response(std::string_view command);

private:
    static constexpr std::string_view API_URL = "https://api.deepseek.com/v1/chat/completions";
    static constexpr std::string_view MODEL = "deepseek-chat";
    static constexpr int MAX_COMMAND_LENGTH = 1000;
    static constexpr int MAX_RESPONSE_LENGTH = 100;
    static constexpr double TEMPERATURE = 0.7;

    static constexpr std::string_view SYSTEM_PROMPT = 
        "Você é meu assistente de terminal. Seja o mais sucinto possível ao "
        "responder, use apenas texto simples, sem aspas desnecessárias. "
        "Se o pedido for um comando, responda apenas ele";

    std::string api_key_;
    CurlClient curl_client_;

    std::string get_api_key() const;
    std::string create_payload(std::string_view command) const;
    void validate_command(std::string_view command) const;
}; 