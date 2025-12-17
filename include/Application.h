#pragma once

#include <ctime>
#include <array>
#include <vector>
#include <random>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Triangulation.h"
#include "Node.h"
#include "Vertex.h"
#include "Shader.h"
#include "Segment.h"
#include "Segment.h"
#include "Triangle.h"
#include "Util.h"
#include "Key.h"

class Application
{
public:
    explicit Application(std::string_view appTitle, int screenWidth, int screenHeight);
    ~Application() noexcept;

    bool active() const noexcept;
    void run();

private:
    void toggleWireframeState();

private:
    std::string title;
    int width, height;

    GLFWwindow* createGlfwContext() const;
    GLFWwindow* glfwContext;

    Shader shader;
    Triangulation triangulation;
    int wireFrameState;

    std::vector<Key> keys;
};
