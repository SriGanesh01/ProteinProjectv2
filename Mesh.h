#pragma once
#include <glad/glad.h>

class Mesh {
public:
	unsigned int VAO, VBO, EBO;
	int indexCount;
	Mesh(float* Tvertices, size_t vertexSize, unsigned int* Tindices, size_t indexSize);
	void Draw();
	void Cleanup();
private:

};