cmake_minimum_required(VERSION 3.16)
project(BugGame3)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML path
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)

# Copy resources to build directory (if exists)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/resources)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

# Copy SFML DLLs to build directory
if(WIN32)
    # Copy SFML DLLs for Release build
    file(GLOB SFML_DLLS "${SFML_DIR}/../../../bin/*.dll")
    if(SFML_DLLS)
        file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
        file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
