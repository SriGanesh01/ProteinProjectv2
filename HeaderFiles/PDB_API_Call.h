#pragma once

#include <string>

class PDBAPICall
{
public:
	PDBAPICall(std::string PDBID);
};

void CallPDBAPI(std::string PDBID);