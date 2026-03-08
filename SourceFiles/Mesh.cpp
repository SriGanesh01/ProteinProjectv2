#include "../HeaderFiles/Mesh.h"


Mesh::Mesh(const std::vector<float>& Tvertices, const std::vector<unsigned int>& Tindices, const std::vector<glm::vec3>& instanceOffsetData, const std::vector<glm::vec3>& instanceColorData) {
    indexCount = static_cast<int>(Tindices.size());
    instanceCount = static_cast<int>(instanceOffsetData.size());

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // Better to bind inside the while loop. So do both

    // Genetate, Bind and add data to VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Tvertices.size() * sizeof(float), Tvertices.data(), GL_STATIC_DRAW);

    // Tell VBO How to read the data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Color
    /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/

    // Instanced position VBOs
    glGenBuffers(1, &instancePositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instancePositionVBO);
    glBufferData(GL_ARRAY_BUFFER, instanceOffsetData.size() * sizeof(glm::vec3), instanceOffsetData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    // Instanced Color VBO
    glGenBuffers(1, &instancedColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instancedColorVBO);
    glBufferData(GL_ARRAY_BUFFER, instanceColorData.size() * sizeof(glm::vec3), instanceColorData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    // Genetate, Bind and add data to EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Tindices.size() * sizeof(unsigned int), Tindices.data(), GL_STATIC_DRAW);
}

void Mesh::Draw() {
    glBindVertexArray(VAO); // Bind here instead of outside if vertex changes often. Bind at both places. Better Practice
    glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0, instanceCount);
}

void Mesh::Cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}