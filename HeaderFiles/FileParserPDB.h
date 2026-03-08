#pragma once

#include <unordered_map>

class FileParserPDB {
public:

	FileParserPDB();
	std::vector<glm::vec3> LocationPointsVectors;
	std::vector<glm::vec3> ColorPointsVector;
	std::unordered_map<std::string, glm::vec3> ColorLookup;

};