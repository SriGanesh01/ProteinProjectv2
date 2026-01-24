
#include "Camera.h"

void Camera::GetMovementInput(GLFWwindow* window, float deltaTime) // , int key, int scancode, int action, int mods
{
    //Camera* TestCam = (Camera*)glfwGetWindowUserPointer(window);

    speed = 1.2f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movementX += speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movementZ -= speed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movementZ += speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movementX -= speed;
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
    view1 = glm::translate(view1, glm::vec3(movementX, 0.0f, movementZ));
    //view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, ));
    proj1 = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100.0f);

    int modelLoc = glad_glGetUniformLocation(myShader.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
    int viewLoc = glad_glGetUniformLocation(myShader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view1));
    int projLoc = glad_glGetUniformLocation(myShader.shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj1));
}