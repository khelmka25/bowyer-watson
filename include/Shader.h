#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>


class Shader
{
public:
    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    ~Shader();
    
    GLuint getProgramHandle(void);

    static std::string loadShaderCode(std::string_view path) noexcept (false);

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    GLuint shaderProgramHandle, vertexShaderHandle, fragmentShaderHandle;
};

