

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Application.h"

#include "Key.h"

using namespace std::literals::string_literals;

Application::Application(std::string&& t_title
    , int t_width
    , int t_height
)
    : title(std::move(t_title))
    , width(t_width)
    , height(t_height)
    , glfwContext(createGlfwContext())
    , shader("shaders/vertexShader.glsl"s, "shaders/fragmentShader.glsl"s)
    , triangulation(100ull)
    , wireFrameState(0)
    , keys({
            Key(GLFW_KEY_W, std::bind(Application::toggleWireframeState, this)),
            Key(GLFW_KEY_R, std::bind(Triangulation::rebuild, &this->triangulation)),
            Key(GLFW_KEY_EQUAL, std::bind(Triangulation::incrementTriangleCount, &this->triangulation)),
            Key(GLFW_KEY_MINUS, std::bind(Triangulation::decrementTriangleCount, &this->triangulation))
        })
{
    std::cout << 
            "------------------------------------------------------------------------------------------\n"
            "Welcome to my Bowyer Watson Algorithm implementation using C++, OpenGL 3.4, and GLEW 2.2.0\n"
            "Press R to build a new triangulation\n"
            "Press - to remove 5 triangles and build a new triangulation\n"
            "Press + to add 5 traingles and build a new triangulation\n"
            "Press W to toggle between wireframe and shaded drawing\n"
            "------------------------------------------------------------------------------------------\n";

    glPolygonMode(GL_FRONT_AND_BACK, wireFrameState ? GL_LINE : GL_FILL);

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    // set frame rate to 60
    glfwSwapInterval(1);
}

bool Application::active() const noexcept {
    return !glfwWindowShouldClose(glfwContext);
}

void Application::run() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& key : keys) {
        key.poll(glfwContext);
    }

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
    glDrawArrays(GL_TRIANGLES, 0, int(triangulation.size() * 3ull));

    // https://registry.khronos.org/EGL/sdk/docs/man/html/eglSwapBuffers.xhtml
    glfwSwapBuffers(glfwContext);
    glfwPollEvents();
}

void Application::toggleWireframeState() {
    wireFrameState ^= 1;
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml
    glPolygonMode(GL_FRONT_AND_BACK, wireFrameState ? GL_LINE : GL_FILL);
}

Application::~Application() noexcept {
    glfwTerminate();
}

GLFWwindow* Application::createGlfwContext() const
{
    // Setup openGL
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("Could not initialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Could not create glfw context");
    }

    glfwMakeContextCurrent(window);

    // Setup callbacks
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int newWidth, int newHeight) -> void {
        glViewport(0, 0, newWidth, newHeight);
        }
    );

    glfwSetErrorCallback([](int error_code, const char* description) -> void {
        std::cout << "GLFW error " << error_code << ": " << description << std::endl;
        }
    );

    // Load glew
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
        glfwTerminate();
        throw std::runtime_error("Could not initialize glad");
    }

    return window;
}
