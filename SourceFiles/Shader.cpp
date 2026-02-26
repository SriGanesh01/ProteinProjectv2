#include "../HeaderFiles/Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string vertexPath, const std::string fragmentPath) {
    // Read vertex shader
    std::string vertexShaderSourceString = ParseShader(vertexPath);
    const char* vertexShaderSourceCharPointer = vertexShaderSourceString.c_str();

    // Read fragment Shader
    std::string fragmentShaderSourceString = ParseShader(fragmentPath);
    const char* fragmentShaderSourceCharPointer = fragmentShaderSourceString.c_str();

    // Create Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCharPointer, NULL);
    glCompileShader(vertexShader);

    // Create Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCharPointer, NULL);
    glCompileShader(fragmentShader);

    // Error Check (Default Code)
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // End of Error Check (Default Code) Code

    // Create Program and tell it to use the shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete created Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Shader::ParseShader(const std::string filepath)
{
    std::ifstream srcFile(filepath);
    std::stringstream srcCode;
    srcCode << srcFile.rdbuf();
    return srcCode.str();
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::cleanup() {
    glDeleteProgram(shaderProgram);
}