#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <functional>

// utility for wrapping GLFW key presses
class Key {
public:
    Key() = default;
    explicit Key(int t_keycode, std::function<void()> t_callback)
        : callback(t_callback)
        , keycode(t_keycode)
        , currentState(0)
        , previousState(0) {
    }

    void poll(GLFWwindow* glfwContext) {
        currentState = (glfwGetKey(glfwContext, keycode) == GLFW_PRESS);

        if (currentState && !previousState) /*Pressed*/ {
            callback();
        }
        else if (currentState && previousState) /*Held*/ {

        }
        else if (!currentState && previousState) /*Released*/ {

        }

        previousState = currentState;
    }

private:
    // 32 bytes
    std::function<void()> callback = nullptr;
    // 4 bytes
    int keycode = 0;
    // 1 byte each
    bool currentState = false;
    bool previousState = false;
};