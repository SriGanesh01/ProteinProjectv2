#pragma once

#include <unordered_map>

class FileParserPDB {
public:

	FileParserPDB();
	std::vector<glm::vec3> LocationPointsVectors;
	std::vector<glm::vec3> ColorPointsVector;
	std::vector<float> WanderVallsRadiusVector;
	std::unordered_map<std::string, glm::vec3> ColorLookup;
	std::unordered_map<std::string, float> WanderVallsRadiusLookup;
	std::unordered_map<std::string, float> CobalentRadiusLookup;

};