#pragma once
#include <vector>

class GenerateCylinderFlatValues
{
public:
	GenerateCylinderFlatValues();

	std::vector<float> cylinderVertices;
	std::vector<unsigned int> cylinderIndices;
};