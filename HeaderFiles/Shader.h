#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
public:
	unsigned int shaderProgram;
	Shader(const std::string vertexPath, const std::string fragmentPath);
	void use();
	void cleanup();
private:
	std::string ParseShader(const std::string filepath);
};