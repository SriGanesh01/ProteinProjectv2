
#include <curl/curl.h>
#include <iostream>

#include "../HeaderFiles/PDB_API_Call.h"


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
		curl_easy_setopt(curl, CURLOPT_URL, PDB_Download_URL.c_str());

		result = curl_easy_perform(curl);

		if (result != CURLE_OK)
		{
			std::cout << PDB_Download_URL << std::endl;
			std::cout << curl << std::endl;
			std::cout << result << std::endl;
			std::cout << "No" << std::endl;
		}
		else {
			std::cout << "Ok" << std::endl;
		}
	}
}