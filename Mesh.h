#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh {
public:
	unsigned int VAO, VBO, EBO;
	int indexCount;
	Mesh(const std::vector<float>& Tvertices, const std::vector<unsigned int>& Tindices);
	void Draw();
	void Cleanup();
private:

};