cmake_minimum_required(VERSION 3.2)

project(PasswordValidator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# definitions
ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

# binary output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# get source files (yes, this isnt considered good practice, i know. but i'm lazyyy :p)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp
                            ${PROJECT_SOURCE_DIR}/source/*.hpp)

# include directories
# include_directories(${PROJECT_SOURCE_DIR}/libraries/.../include/)
include_directories(${PROJECT_SOURCE_DIR}/libraries/spdlog/include/)
include_directories(${PROJECT_SOURCE_DIR}/libraries/libfmt/include/)

add_executable(PasswordValidator ${SRC_FILES})

# link necessary static libraries
# target_link_libraries(PasswordValidator ${PROJECT_SOURCE_DIR}/libraries/.../....a)
target_link_libraries(PasswordValidator ${PROJECT_SOURCE_DIR}/libraries/spdlog/libspdlog.a)
target_link_libraries(PasswordValidator ${PROJECT_SOURCE_DIR}/libraries/libfmt/libfmt.a)
