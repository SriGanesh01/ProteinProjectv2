#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
	unsigned int VAO, VBO, EBO, instancePositionVBO, instancedColorVBO, instancedScaleVBO;
	int indexCount;
	int instanceCount;
	Mesh(const std::vector<float>& Tvertices, const std::vector<unsigned int>& Tindices, const std::vector<glm::vec3>& instanceOffsetData, const std::vector<glm::vec3>& instanceColorData, const std::vector<float>& instancedScaleData);
	Mesh(const std::vector<float>& Tvertices, const std::vector<unsigned int>& Tindices);
	void Draw();
	void Cleanup();
private:

};