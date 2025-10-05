cmake_minimum_required(VERSION 3.20)
project(bowyer_watson CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)

target_compile_options(${PROJECT_NAME} 
    PRIVATE 
    -Wconversion 
    -Wall 
    -Wextra
    -Wpedantic
)

aux_source_directory(src SOURCE_DIR)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw 
    GLEW::GLEW
    opengl32
)