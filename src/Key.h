#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>

// utility for wrapping GLFW key presses
class Key {
public:
    Key(int t_keycode, std::function<void()> t_callback)
        : callback(t_callback)
        , keycode(t_keycode)
        , currentState(0)
        , previousState(0) {
    }

    void poll(GLFWwindow* glfwContext) {
        currentState = false;
        if (glfwGetKey(glfwContext, keycode) == GLFW_PRESS) {
            currentState = true;
        }

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
    std::function<void()> callback;
    // 4 bytes
    int keycode;
    // 1 byte each
    bool currentState, previousState;
};