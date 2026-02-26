#pragma once
#include <vector>

class GenerateCylinderValues
{
public:
	GenerateCylinderValues();

	std::vector<float> cylinderVertices;
	std::vector<unsigned int> cylinderIndices;
};