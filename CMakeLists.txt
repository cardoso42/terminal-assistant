cmake_minimum_required(VERSION 3.14)
project(DeepSeekTerminalAssistant)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(assistant main.cpp)

# Include path for nlohmann/json (header-only)
target_include_directories(assistant PRIVATE ${CMAKE_SOURCE_DIR})

# Find libcurl
find_package(CURL REQUIRED)
target_link_libraries(assistant PRIVATE CURL::libcurl)
