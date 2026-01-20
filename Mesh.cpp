#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& Tvertices, const std::vector<unsigned int>& Tindices) {
    indexCount = static_cast<int>(Tindices.size());

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

    // Genetate, Bind and add data to EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Tindices.size() * sizeof(unsigned int), Tindices.data(), GL_STATIC_DRAW);
}

void Mesh::Draw() {
    glBindVertexArray(VAO); // Bind here instead of outside if vertex changes often. Bind at both places. Better Practice
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Mesh::Cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}