#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"


class Camera {
public:
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	void Use(int display_w, int display_h, Shader myShader);
	void GetMovementInput(GLFWwindow* window, int key, int scancode, int action, int mods);
private:

};