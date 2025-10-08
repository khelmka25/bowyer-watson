#include "shader.h"

#include <filesystem>

Shader::Shader(std::string&& vertexPath, std::string&& fragmentPath)
{
    /*Vertex Shader*/

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
    vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource = Shader::loadShaderCode(vertexPath);
    const char* vertexShaderSourcePtr = vertexShaderSource.c_str();

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
    glShaderSource(vertexShaderHandle, 1, &vertexShaderSourcePtr, nullptr);

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml
    glCompileShader(vertexShaderHandle);

    // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml
    GLint vertexStatus;
    glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &vertexStatus);
    if (vertexStatus != GL_TRUE) {
        GLchar infoLog[1024];
        // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml
        glGetShaderInfoLog(vertexShaderHandle, 1024, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }

    /*Fragment Shader*/

    fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource = Shader::loadShaderCode(fragmentPath);
    const char* fragmentShaderSourcePtr = fragmentShaderSource.c_str();

    glShaderSource(fragmentShaderHandle, 1, &fragmentShaderSourcePtr, nullptr);
    glCompileShader(fragmentShaderHandle);

    GLint fragmentStatus;
    glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &fragmentStatus);
    if (fragmentStatus != GL_TRUE) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(fragmentShaderHandle, 1024, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }

    // Create the shader program with Id
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
    shaderProgramHandle = glCreateProgram();

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
    glAttachShader(shaderProgramHandle, vertexShaderHandle);
    glAttachShader(shaderProgramHandle, fragmentShaderHandle);

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
    glLinkProgram(shaderProgramHandle);

    GLint shaderStatus;
    glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &shaderStatus);
    if (shaderStatus != GL_TRUE) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(shaderProgramHandle, 1024, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
    glUseProgram(shaderProgramHandle);
}

Shader::~Shader()
{
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml
    glDeleteProgram(shaderProgramHandle);
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml
    glDeleteShader(vertexShaderHandle);
    glDeleteShader(fragmentShaderHandle);
}

std::string Shader::loadShaderCode(std::string path) noexcept(false) {
    std::ifstream sourceCodeFile(path);
    if (sourceCodeFile.fail()) {
        std::cout << "Failed to open " << std::quoted(path) << std::endl;
        return {};
    }

    std::string line, source_code;
    while (std::getline(sourceCodeFile, line, '\n')) {
        source_code += (line + '\n');
    }

    return source_code;
}

GLuint Shader::getProgramHandle(void)
{
    return shaderProgramHandle;
}

/// Might use these later alter the generated triangles' colors
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderProgramHandle, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgramHandle, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgramHandle, name.c_str()), value);
}
