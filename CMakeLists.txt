cmake_minimum_required(VERSION 3.2)

project(PswdValitor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# definitions
ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
# binary output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# function to resolve lib implementations
function(resolve_impl LOCATION)
    file (GLOB_RECURSE FILES "*.cpp" "*.c")

    set (LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")

    foreach (TMP_PATH ${FILES})
        string (FIND ${TMP_PATH} ${LIBS_DIR} LIBS_DIR_FOUND)

        if (${LIBS_DIR_FOUND} GREATER -1)
            message(STATUS "INCLUDING IMPL: " ${TMP_PATH})
            continue()
        endif ()

        list (REMOVE_ITEM FILES ${TMP_PATH})
    endforeach(TMP_PATH)

    set(${LOCATION} ${FILES} PARENT_SCOPE)
endfunction()
resolve_impl(LIBS_IMPL_FILES)

# function to resolve both header and source files
function(resolve_files TYPE LOCATION)
    if (${TYPE} STREQUAL "HEADER")
        file (GLOB_RECURSE FILES "*.hpp" "*.h")
    elseif(${TYPE} STREQUAL "SOURCE")
        file (GLOB_RECURSE FILES "*.cpp" "*.c")
    endif()

    # ignore directories
    set (LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")
    set (BUILD_DIR "${PROJECT_SOURCE_DIR}/build")

    foreach (TMP_PATH ${FILES})
        string (FIND ${TMP_PATH} ${LIBS_DIR} LIBS_DIR_FOUND)
        string (FIND ${TMP_PATH} ${BUILD_DIR} BUILD_DIR_FOUND)

        if (${LIBS_DIR_FOUND} GREATER -1 OR ${BUILD_DIR_FOUND} GREATER -1)
            list (REMOVE_ITEM FILES ${TMP_PATH})
            continue()
        endif ()

        message(STATUS "INCLUDING ${TYPE}: " ${TMP_PATH})
    endforeach(TMP_PATH)

    set(${LOCATION} ${FILES} PARENT_SCOPE)
endfunction()
resolve_files("HEADER" HDR_FILES)
resolve_files("SOURCE" SRC_FILES)

# include directories
# include_directories(${PROJECT_SOURCE_DIR}/libs/.../)

add_executable(main ${HDR_FILES_FILES} ${SRC_FILES} ${LIBS_IMPL_FILES})

# link necessary static libraries
# target_link_libraries(main ${PROJECT_SOURCE_DIR}/libs/.../*.a)