cmake_minimum_required(VERSION 3.0.0)
project(PhysicsEngineTest)

add_executable(PhysicsEngineTest engine.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-system sfml-window sfml-graphics)
