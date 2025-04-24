#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <curl/curl.h>

// CURL Resource Management
struct CurlDeleter {
    void operator()(CURL* curl) const;
};

struct CurlSlistDeleter {
    void operator()(curl_slist* list) const;
};

using CurlPtr = std::unique_ptr<CURL, CurlDeleter>;
using CurlSlistPtr = std::unique_ptr<curl_slist, CurlSlistDeleter>;

// RAII wrapper for CURL initialization
class CurlGlobal {
public:
    CurlGlobal();
    ~CurlGlobal();
    
    // Prevent copying
    CurlGlobal(const CurlGlobal&) = delete;
    CurlGlobal& operator=(const CurlGlobal&) = delete;
};

class CurlClient {
public:
    CurlClient();
    std::string post(std::string_view url, std::string_view data, const std::vector<std::string>& headers);

private:
    static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);
    CurlGlobal curl_global_;
}; 