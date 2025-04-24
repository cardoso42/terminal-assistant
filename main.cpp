#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <curl/curl.h>
#include "json.hpp"

#define ANSWER_MAX_TOKENS 100

std::string get_env_var(const std::string& key) {
    const char* val = std::getenv(key.c_str());
    if (!val) throw std::runtime_error("Variável de ambiente " + key + " não definida.");
    return std::string(val);
}

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string get_assistant_response(const std::string& command) {
    try {
        std::string system_prompt = 
            "Você é meu assistente de terminal. "
            "Me ajude com o pedido a seguir, tente ser o mais sucinto possível. "
            "Se o pedido for de um comando, responda apenas o comando, "
            "sem textos adicionais ou formatação.";

        std::string api_key = get_env_var("DEEPSEEK_API_KEY");

        nlohmann::json payload = {
            {"model", "deepseek-chat"},
            {"messages", {
                {{"role", "system"}, {"content", system_prompt}},
                {{"role", "user"}, {"content", command}}
            }},
            {"max_tokens", ANSWER_MAX_TOKENS},
            {"temperature", 0.2}
        };

        std::string response_string;
        std::string payload_str = payload.dump();

        CURL* curl = curl_easy_init();
        if (!curl) throw std::runtime_error("Erro ao inicializar cURL");

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.deepseek.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) throw std::runtime_error("Erro ao consultar a API: " + std::string(curl_easy_strerror(res)));

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        nlohmann::json response_json = nlohmann::json::parse(response_string);
        return response_json["choices"][0]["message"]["content"];
    }
    catch (const std::exception& e) {
        return std::string("Erro: ") + e.what();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <comando>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string answer = get_assistant_response(command);
    std::cout << "Resposta do assistente: " << answer << std::endl;

    return 0;
}
