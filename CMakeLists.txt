cmake_minimum_required(VERSION 3.10)
project(assistant VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force installation to ~/bin
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}" CACHE PATH "Installation prefix" FORCE)

# Find required packages
find_package(CURL REQUIRED)

# Add format target
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*.[ch]pp
        ${PROJECT_SOURCE_DIR}/include/*.[ch]pp
        ${PROJECT_SOURCE_DIR}/tests/*.[ch]pp
    )
    
    # Remove json.hpp from the list of files to format
    list(REMOVE_ITEM ALL_SOURCE_FILES ${PROJECT_SOURCE_DIR}/include/json.hpp)
    
    # Process files in smaller batches
    foreach(FILE ${ALL_SOURCE_FILES})
        add_custom_command(
            OUTPUT ${FILE}.formatted
            COMMAND ${CLANG_FORMAT} -i ${FILE}
            COMMAND touch ${FILE}.formatted
            DEPENDS ${FILE}
            COMMENT "Formatting ${FILE}..."
        )
        list(APPEND FORMATTED_FILES ${FILE}.formatted)
    endforeach()
    
    # Add cleanup command
    add_custom_command(
        OUTPUT format_cleanup
        COMMAND ${CMAKE_COMMAND} -E remove ${FORMATTED_FILES}
        DEPENDS ${FORMATTED_FILES}
        COMMENT "Cleaning up temporary files..."
    )
    
    add_custom_target(format
        DEPENDS format_cleanup
        COMMENT "Formatting all source files..."
    )
endif()

# Add subdirectories
add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Install rules
install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
