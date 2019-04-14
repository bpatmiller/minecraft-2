cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME minecraft)
project(${PROJECT_NAME})

# cpp version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# cflags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -fmax-errors=1 -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# add source files
aux_source_directory("src" SOURCES)

# add glm


# create executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})