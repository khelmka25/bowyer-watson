#pragma once

#include <ctime>
#include <array>
#include <vector>
#include <random>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Triangulation.h"
#include "node.h"
#include "vertex.h"
#include "shader.h"
#include "segment.h"
#include "segment.h"
#include "triangle.h"
#include "Util.h"
#include "Key.h"

class Application
{
public:
    explicit Application(std::string&& appTitle, int screenWidth, int screenHeight);
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
