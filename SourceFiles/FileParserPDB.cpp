#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../HeaderFiles/FileParserPDB.h"

FileParserPDB::FileParserPDB()
{
	std::ifstream ParsedPDBfile("PDBDatas/pdb2c0k.ent");
	if (!ParsedPDBfile.is_open())
	{
		std::cout << "FILE FAILED TO OPEN\n";
		return;
	}
	std::string EachLine;

	ColorLookup = {
		{"H", {1.0f, 1.0f, 1.0f}},
		{"C", {0.5f, 0.5f, 0.5f}},
		{"N", {0.0f, 0.0f, 1.0f}},
		{"O", {1.0f, 0.0f, 0.0f}},
		{"S", {1.0f, 1.0f, 0.0f}},
		{"P", {1.0f, 0.5f, 0.0f}},
		{"F", {0.0f, 0.8f, 0.0f}},
		{"CL", {0.0f, 0.8f, 0.0f}},
		{"BR", {0.6f, 0.13f, 0.0f}},
		{"I", {0.58f, 0.0f, 0.83f}}
	};

	//std::cout << ColorLookup["J"].x << std::endl;

	while (std::getline(ParsedPDBfile, EachLine))
	{
		std::string record = EachLine.substr(0, 6);
		
		if (record == "ATOM  " || record == "HETATM")
		{
			int serial = std::stof(EachLine.substr(6, 5));
			std::string atomName = EachLine.substr(12, 4);
			std::string altLoc = EachLine.substr(16, 1);
			std::string residueName = EachLine.substr(17, 3);
			std::string chainID = EachLine.substr(21, 1);
			int residueSeq = std::stof(EachLine.substr(22, 4));
			std::string insertionCode = EachLine.substr(26, 1);

			float xCoord = std::stof(EachLine.substr(30, 8));
			float yCoord = std::stof(EachLine.substr(38, 8));
			float zCoord = std::stof(EachLine.substr(46, 8));

			float occupancy = std::stof(EachLine.substr(54, 6));
			float tempFactor = std::stof(EachLine.substr(60, 6));

			std::string element = EachLine.substr(76, 2);
			std::string charge = EachLine.substr(78, 2);

			 /*std::cout << record << " " << serial << " " << atomName << " " << altLoc << " " 
			 << residueName << " " << chainID << " " << residueSeq << " " << insertionCode 
			 << " " << xCoord << " " << yCoord << " " << zCoord << " " << occupancy << " " 
			 << tempFactor << " " << element << " " << charge << std::endl;*/

			element.erase(remove(element.begin(), element.end(), ' '), element.end());

			auto it = ColorLookup.find(element);

			if (it != ColorLookup.end())
			{
				FileParserPDB::ColorPointsVector.push_back(glm::vec3(it->second));
			}
			else
			{
				FileParserPDB::ColorPointsVector.push_back(glm::vec3(1.0f, 0.2f, 0.8f));
			}

			

			FileParserPDB::LocationPointsVectors.push_back(glm::vec3(xCoord, yCoord, zCoord));

			
		}

	}
	ParsedPDBfile.close();
}