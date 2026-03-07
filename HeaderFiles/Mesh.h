#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
	unsigned int VAO, VBO, EBO, instanceVBO;
	int indexCount;
	int instanceCount;
	Mesh(const std::vector<float>& Tvertices, const std::vector<unsigned int>& Tindices, const std::vector<glm::vec3>& instanceOffsetData);
	void Draw();
	void Cleanup();
private:

};