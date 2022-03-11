cmake_minimum_required(VERSION 3.2)

project(PasswordValidator)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b -Wall -Wextra")

# definitions
add_definitions(-DUNICODE -D_UNICODE -DCMAKE_EXPORT_COMPILE_COMMANDS)

# binary output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

set(SRC_FILES ${PROJECT_SOURCE_DIR}/source/PasswordValidator.cpp
              ${PROJECT_SOURCE_DIR}/source/parser/EntropyParser.cpp
              ${PROJECT_SOURCE_DIR}/source/entropy/PasswordEntropy.cpp
              ${PROJECT_SOURCE_DIR}/source/entropy/validation/PasswordValidation.cpp)

# external projects
add_subdirectory(external/libfmt/)

# include directories
# include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/external/libfmt/include/
                    ${PROJECT_SOURCE_DIR}/external/spdlog/include/)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# link necessary static libraries
# target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/)
target_link_libraries(${PROJECT_NAME} fmt)
