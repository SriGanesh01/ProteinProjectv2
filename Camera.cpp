
#include "Camera.h"

void Camera::GetMovementInput(GLFWwindow* window, float deltaTime) // , int key, int scancode, int action, int mods
{
    //Camera* TestCam = (Camera*)glfwGetWindowUserPointer(window);

    speed = 1.2f;
    velocity = speed * deltaTime;

    glm::vec3 right = glm::cross(forward, up);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += forward * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += up * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position -= up * velocity;   
}

void Camera::GetMouseInput(GLFWwindow* window)
{
    double xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    glm::vec3 direction;
    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    direction.y = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    direction.z = sin(glm::radians(pitch));
    forward = glm::normalize(direction);



}

void Camera::Use(int display_w, int display_h, Shader myShader) {

    /*double crntTime = glfwGetTime(); 
    if (crntTime - prevTime >= 1 / 60) {
        rotation += 0.5f;
        prevTime = crntTime;
    }*/


    glm::mat4 model1 = glm::mat4(1.0f);
    glm::mat4 view1 = glm::mat4(1.0f);
    glm::mat4 view2 = glm::mat4(1.0f);
    glm::mat4 proj1 = glm::mat4(1.0f);

    //model1 = glm::rotate(model1, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    //view2 = glm::rotate(view2, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    //view1 = glm::translate(view1, glm::vec3(movementX, movementY, movementZ));
    //view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, ));

    view1 = glm::lookAt(position, position + forward, up);
    proj1 = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100.0f);

    int modelLoc = glad_glGetUniformLocation(myShader.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
    int viewLoc = glad_glGetUniformLocation(myShader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view1));
    int projLoc = glad_glGetUniformLocation(myShader.shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj1));
}