#include "ReadCSV.h"

extern std::vector<ObjectCSV> objects;
extern std::map<std::string, int> idMap;
extern std::vector<std::string> idToString;

std::vector<ObjectCSV> ReadObjectsCSV() {
	//Read the objects csv file
	std::ifstream objectsFile;
	objectsFile.open("data\\objects.csv");

	std::vector<ObjectCSV> objects;

	std::string object;

	int id{ 0 };

	//Ignore the first line
	std::getline(objectsFile, object);

	ObjectCSV tmpObject;

	while (!objectsFile.eof()) {
		std::getline(objectsFile, object);
		if (object == "") continue; // ignore empty lines

		//Generate a vector of strings, each element is the string seperated by a comma
		std::istringstream ss{ object };
		std::string token;
		std::vector<std::string> tokens;

		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		tmpObject.name = tokens[0];

		if (tokens[1] == "CONFIGURATION") {
			tmpObject.group = CONFIGURATION;
		}
		else if (tokens[1] == "ENVIRONMENT") {
			tmpObject.group = ENVIRONMENT;
		}
		else if (tokens[1] == "PROTECTIVE") {
			tmpObject.group = PROTECTIVE;
		}
		else if (tokens[1] == "REWARD") {
			tmpObject.group = REWARD;
		}
		else if (tokens[1] == "HAZARD") {
			tmpObject.group = HAZARD;
		}
		else
		{
			continue;
		}
		
		if (tokens[1] == "CONFIGURATION") {
			tmpObject.spriteID[4] = Play::GetSpriteId((tokens[2] + "_panel").c_str());
		}
		else {
			for (int i = 0; i < 4; i++) {
				tmpObject.spriteID[i] = Play::GetSpriteId((tokens[2] + "_R" + std::string{(char)('A' + i)}).c_str());
			}
			tmpObject.spriteID[4] = Play::GetSpriteId((tokens[2] + "_panel").c_str());
		}

		tmpObject.id = id;

		//Add the item to a list of objects and update the map of string ID's to number ID's for more efficient comparisons
		idToString.push_back(tokens[3]);
		idMap[tokens[3]] = id++;

		objects.push_back(tmpObject);
	}

	objectsFile.close();

	return objects;
}

int GetSpriteIDFromObjectID(int objID, int rot) {
	for (ObjectCSV objCSV : objects) {
		if (objCSV.id == objID) {
			return objCSV.spriteID[rot];
		}
	}
	return -1;
}