cmake_minimum_required(VERSION 3.10)
project(assistant VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force installation to ~/bin
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}" CACHE PATH "Installation prefix" FORCE)

# Find required packages
find_package(CURL REQUIRED)

# Add subdirectories
add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Install rules
install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
