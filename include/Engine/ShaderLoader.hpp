#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class ShaderLoader {
    public:
        GLuint CreateProgram(const std::string vertexShaderFileName, const std::string fragmentShaderFileName);
    private:
        std::string readShader(const std::string filename);
        GLuint createShader(GLenum shaderType, std::string source, const std::string shaderName);
};