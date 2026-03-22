
#include <curl/curl.h>
#include <iostream>
#include <fstream>

#include "../HeaderFiles/PDB_API_Call.h"

size_t WriteToPDBFile(char* ActualContent, size_t itemSize, size_t numberOfItems, void* ignoreForNow_UsedToPassInAdditionalObjectsLikeFilesToWriteOutputIn) // Is a must to have all these arguements; This is a callback function btw;
{
	size_t bytes = itemSize * numberOfItems; // To verify that all data is processed correctly; Just have this thing;

	std::cout << bytes << std::endl;

	/*for (int i = 0; i < bytes; i++)
	{
		std::cout << buffer[i];
	}*/

	FILE* PDBfile = (FILE*)ignoreForNow_UsedToPassInAdditionalObjectsLikeFilesToWriteOutputIn;
	

	return fwrite(ActualContent, itemSize, numberOfItems, PDBfile);
}


void CallPDBAPI(std::string PDBID)
{
	//curl -o "https ://files.rcsb.org/download/" + PDBID + ".pdb"

	// Make sure to do a call back to the above web link download stuff

	std::string PDB_Download_URL = "https://files.rcsb.org/download/" + PDBID + ".pdb";
	std::string SavingFileName = PDBID + ".pdb";

	CURL* curl;
	CURLcode result;

	curl = curl_easy_init();

	if (curl != NULL)
	{
		FILE* PDBFile = fopen(SavingFileName.c_str(), "wb");
		// Set Options
		curl_easy_setopt(curl, CURLOPT_URL, PDB_Download_URL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToPDBFile); // Rewrites Defauult output behaviour; Which is to stdout to the terminal;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, PDBFile);


		// Perform Actions
		CURLcode result = curl_easy_perform(curl);

		if (result != CURLE_OK)
		{
			std::cout << "File Not Found" << std::endl;
		}

		fclose(PDBFile);
		curl_easy_cleanup(curl);
	}
}