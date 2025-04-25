# Add executable
add_executable(assistant
    main.cpp
    api_client.cpp
    curl_client.cpp
    command_executor.cpp
)

# Include directories
target_include_directories(assistant
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CURL_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(assistant
    PRIVATE
        CURL::libcurl
)

# Install rules
install(TARGETS assistant
    RUNTIME DESTINATION bin) 