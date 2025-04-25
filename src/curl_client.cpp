#include "curl_client.hpp"
#include <stdexcept>

void CurlDeleter::operator()(CURL* curl) const {
    curl_easy_cleanup(curl);
}

CurlGlobal::CurlGlobal() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CurlGlobal::~CurlGlobal() {
    curl_global_cleanup();
}

CurlClient::CurlClient() : curl_global_() {}

std::string CurlClient::post(std::string_view url, std::string_view data, const std::vector<std::string>& headers) {
    std::string response_string;
    CurlPtr curl(curl_easy_init());
    if(!curl) throw std::runtime_error("Erro ao inicializar cURL");

    curl_slist* raw_headers = nullptr;
    for(const auto& h : headers) {
        raw_headers = curl_slist_append(raw_headers, h.c_str());
    }
    CurlSlistPtr header_list(raw_headers, &curl_slist_free_all);

    curl_easy_setopt(curl.get(), CURLOPT_URL, url.data());
    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, header_list.get());
    curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, data.data());
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, &CurlClient::write_callback);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl.get());
    if (res != CURLE_OK) {
        throw std::runtime_error("Erro ao consultar a API: " + std::string(curl_easy_strerror(res)));
    }

    return response_string;
}

size_t CurlClient::write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    auto& response = *static_cast<std::string*>(userp);
    response.append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
} 