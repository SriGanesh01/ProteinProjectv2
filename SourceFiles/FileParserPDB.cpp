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

			/* std::cout << record << " " << serial << " " << atomName << " " << altLoc << " " 
			 << residueName << " " << chainID << " " << residueSeq << " " << insertionCode 
			 << " " << xCoord << " " << yCoord << " " << zCoord << " " << occupancy << " " 
			 << tempFactor << " " << element << " " << charge << std::endl;*/

			FileParserPDB::LocationPointsVectors.push_back(glm::vec3(xCoord, yCoord, zCoord));
		}

	}
	ParsedPDBfile.close();
}