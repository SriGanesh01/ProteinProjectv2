#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../HeaderFiles/FileParserPDB.h"

FileParserPDB::FileParserPDB(std::string PDBID)
{
	std::string Path = "PDBDatas/" + PDBID + ".pdb";
	std::ifstream ParsedPDBfile(Path);
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

	//ColorLookup = {
	//{"H",  {0.00f, 0.80f, 1.00f}}, // Neon Cyan
	//{"C",  {0.20f, 0.20f, 0.20f}}, // Deep Charcoal
	//{"N",  {0.70f, 0.00f, 1.00f}}, // Electric Purple
	//{"O",  {1.00f, 0.00f, 0.40f}}, // Hot Pink
	//{"S",  {0.00f, 1.00f, 0.50f}}, // Spring Green
	//{"P",  {1.00f, 0.50f, 0.00f}}, // Vivid Orange
	//{"F",  {0.50f, 1.00f, 0.00f}}, // Lime
	//{"CL", {0.50f, 1.00f, 0.00f}}, // Lime
	//{"BR", {1.00f, 0.20f, 0.20f}}, // Bright Red
	//{"I",  {0.40f, 0.40f, 1.00f}}, // Royal Blue
	//{"FE", {1.00f, 0.84f, 0.00f}}  // Gold
	//};

	//ColorLookup = {
	//{"H",  {0.95f, 0.95f, 0.95f}}, // Off-white
	//{"C",  {0.45f, 0.45f, 0.47f}}, // Soft Slate
	//{"N",  {0.55f, 0.70f, 1.00f}}, // Baby Blue
	//{"O",  {1.00f, 0.55f, 0.55f}}, // Salmon/Coral
	//{"S",  {1.00f, 0.90f, 0.50f}}, // Pale Gold
	//{"P",  {1.00f, 0.70f, 0.40f}}, // Peach
	//{"F",  {0.60f, 0.90f, 0.60f}}, // Mint
	//{"CL", {0.60f, 0.90f, 0.60f}}, // Mint
	//{"BR", {0.80f, 0.40f, 0.40f}}, // Terra Cotta
	//{"I",  {0.70f, 0.50f, 0.90f}}, // Lavender
	//{"FE", {0.75f, 0.65f, 0.55f}}  // Warm Grey
	//};

	//ColorLookup = {
	//{"H",  {0.80f, 1.00f, 1.00f}}, // Ice Blue
	//{"C",  {0.10f, 0.30f, 0.40f}}, // Dark Teal
	//{"N",  {0.00f, 0.50f, 0.80f}}, // Deep Sea Blue
	//{"O",  {0.20f, 0.80f, 0.60f}}, // Emerald/Seafoam
	//{"S",  {0.60f, 1.00f, 0.20f}}, // Bright Moss
	//{"P",  {0.00f, 1.00f, 0.80f}}, // Turquoise
	//{"F",  {0.50f, 0.90f, 0.50f}}, // Sea Glass
	//{"CL", {0.50f, 0.90f, 0.50f}}, // Sea Glass
	//{"BR", {0.20f, 0.40f, 0.60f}}, // Slate Blue
	//{"I",  {0.10f, 0.20f, 0.50f}}, // Navy
	//{"FE", {0.00f, 0.30f, 0.20f}}  // Deep Forest
	//};

	//ColorLookup = {
	//{"H",  {1.00f, 1.00f, 1.00f}}, // Pure White
	//{"C",  {0.40f, 0.40f, 0.40f}}, // Bright Silver
	//{"N",  {0.00f, 0.40f, 1.00f}}, // Electric Blue
	//{"O",  {1.00f, 0.00f, 0.00f}}, // Vivid Red
	//{"S",  {1.00f, 1.00f, 0.00f}}, // Bright Yellow
	//{"P",  {1.00f, 0.50f, 0.00f}}, // Neon Orange
	//{"F",  {0.00f, 1.00f, 0.00f}}, // Acid Green
	//{"CL", {0.00f, 1.00f, 0.00f}}, // Acid Green
	//{"BR", {1.00f, 0.20f, 0.20f}}, // Crimson
	//{"I",  {0.60f, 0.00f, 1.00f}}, // Electric Purple
	//{"FE", {1.00f, 0.80f, 0.00f}}  // Bright Gold
	//};

	//ColorLookup = {
	//{"H",  {0.20f, 0.00f, 0.00f}}, // Deep Maroon (Inv: Ice Blue)
	//{"C",  {0.90f, 0.70f, 0.60f}}, // Warm Sand (Inv: Dark Teal)
	//{"N",  {1.00f, 0.50f, 0.20f}}, // Bright Amber (Inv: Sea Blue)
	//{"O",  {0.80f, 0.20f, 0.40f}}, // Magenta/Rose (Inv: Emerald)
	//{"S",  {0.40f, 0.00f, 0.80f}}, // Deep Purple (Inv: Bright Moss)
	//{"P",  {1.00f, 0.00f, 0.20f}}, // Hot Pink (Inv: Turquoise)
	//{"F",  {0.50f, 0.10f, 0.50f}}, // Plum (Inv: Sea Glass)
	//{"CL", {0.50f, 0.10f, 0.50f}}, // Plum
	//{"BR", {0.80f, 0.60f, 0.40f}}, // Bronze (Inv: Slate Blue)
	//{"I",  {0.90f, 0.80f, 0.50f}}, // Pale Gold (Inv: Navy)
	//{"FE", {1.00f, 0.70f, 0.80f}}  // Soft Pink (Inv: Deep Forest)
	//};

	WanderVallsRadiusLookup = {
		{"H",  1.20f}, {"HE", 1.40f}, {"LI", 1.82f}, {"BE", 1.53f},
		{"B",  1.92f}, {"C",  1.70f}, {"N",  1.55f}, {"O",  1.52f},
		{"F",  1.47f}, {"NE", 1.54f}, {"NA", 2.27f}, {"MG", 1.73f},
		{"AL", 1.84f}, {"SI", 2.10f}, {"P",  1.80f}, {"S",  1.80f},
		{"CL", 1.75f}, {"AR", 1.88f}, {"K",  2.75f}, {"CA", 2.31f},
		{"NI", 1.63f}, {"CU", 1.40f}, {"ZN", 1.39f}, {"GA", 1.87f},
		{"GE", 2.11f}, {"AS", 1.85f}, {"SE", 1.90f}, {"BR", 1.85f},
		{"KR", 2.02f}, {"RB", 3.03f}, {"SR", 2.49f}, {"PD", 1.63f},
		{"AG", 1.72f}, {"CD", 1.58f}, {"IN", 1.93f}, {"SN", 2.17f},
		{"SB", 2.06f}, {"TE", 2.06f}, {"I",  1.98f}, {"XE", 2.16f},
		{"CS", 3.43f}, {"BA", 2.68f}, {"PT", 1.75f}, {"AU", 1.66f},
		{"HG", 1.55f}, {"TL", 1.96f}, {"PB", 2.02f}, {"BI", 2.07f},
		{"PO", 1.97f}, {"AT", 2.02f}, {"RN", 2.20f}, {"FR", 3.48f},
		{"RA", 2.83f}, {"U",  1.86f}
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

			auto it2 = WanderVallsRadiusLookup.find(element);

			if (it2 != WanderVallsRadiusLookup.end())
			{
				FileParserPDB::WanderVallsRadiusVector.push_back(it2->second);
			}
			else
			{
				FileParserPDB::WanderVallsRadiusVector.push_back(1);
			}

			

			FileParserPDB::LocationPointsVectors.push_back(glm::vec3(xCoord, yCoord, zCoord));

			
		}

	}
	ParsedPDBfile.close();
}