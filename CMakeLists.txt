cmake_minimum_required(VERSION 3.20)
project(bowyer_watson)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# internal library
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)
add_library(engine STATIC ${SOURCES})
target_include_directories(engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
)

# glfw
add_subdirectory(deps/glfw)

# glad
# aux_source_directory(${CMAKE_SOURCE_DIR}/deps/glad/src GLAD_SOURCE)
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/deps/glad/src/glad.c)
target_include_directories(glad PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include
)

# main project
add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE
    engine
    glfw
    glad
    opengl32
)

target_compile_options(${PROJECT_NAME} 
    PRIVATE 
    -Wconversion 
    -Wall 
    -Wextra
    -Wpedantic
    -Wfloat-equal
)