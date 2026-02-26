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

	/*float movementX = 0.0f;
	float movementY = 0.0f;
	float movementZ = 0.0f;*/

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstMouse = true;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float sensitivity = 0.1f;

	float xLast = 0.0f;
	float yLast = 0.0f;

	float speed;
	float velocity;

	void Use(int display_w, int display_h, Shader myShader);
	void GetMovementInput(GLFWwindow* window, float deltaTime);
	void GetMouseInput(GLFWwindow* window, float width, float height);
private:

};