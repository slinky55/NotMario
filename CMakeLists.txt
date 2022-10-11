cmake_minimum_required(VERSION 3.20)
project(NotMario)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(3rdparty/sfml)
add_subdirectory(3rdparty/entt)

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-system sfml-window sfml-graphics
        EnTT::EnTT)
