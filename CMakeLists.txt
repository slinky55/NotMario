cmake_minimum_required(VERSION 3.23)
project(NotMario)

set(CMAKE_CXX_STANDARD 20)

if (MACOS)
    include_directories(/usr/local/include include)
    link_directories(/usr/local/lib)
elseif(UNIX)
    include_directories(include)
endif()

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-system sfml-window sfml-graphics)
