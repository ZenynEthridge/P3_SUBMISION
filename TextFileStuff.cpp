#include "TextFileStuff.h"

// Zenyn Ethridge, Jesse Orozco, Geremias Montano-Izazaga


/*The purpose of this function is to read in data which was
* directly copy pasted from tables found on website:
* https://www.cnrfc.noaa.gov/monthly_precip.php
* much of the formatting is confusing for this reason*/

void readHashes(std::string line, std::string& region, int& year) 
{							// reads year and region data from govt                                           
	if (isdigit(line[1]))	// text file, which has been manually prefixed     
	{						// by programmer with a hash '#' symbol
		std::string yearStr = "";
		for (size_t i = 1; i < 5; i++) { yearStr += line[i]; }
		year = std::stoi(yearStr);
		region = ""; // region must be reset because it is not included in all years
	}
	else
	{
		region = "";
		size_t i = 0;
		while (line[++i]) if (line[i] != '#') { region += line[i]; }
	}
}
void initializeLocations( // processes location and rain data from govt text file
	std::string fileName,  
	LocationArray &locations)
{
	const int numLines = 5368;
	std::fstream file(fileName, std::ios::in);
	std::string line = "";
	std::string region = "";
	int year = 0, index;

	Location currentLocation = Location("NULL", "NULL", "NULL");
	int lineNumber = 0;
	while (getline(file, line) && lineNumber < 10000)
	{
		if (line[0] == '#') { readHashes(line, region, year); }
		else
		{
			currentLocation = Location(line, year);
			if (!currentLocation.hasRegion()) { currentLocation.setRegion(region); }
			index = locations.find(currentLocation);
			if (index >= 0) { locations.set(locations.at(index) + currentLocation, index); }
			else { locations.pushback(currentLocation); }
		}
		lineNumber++;
		std::cout << 
			std::fixed << std::setprecision(5) << 
			(lineNumber * 1.0 / numLines) * 100.0 << " %\n";
	}
	std::cout << "\n\n\n" << (lineNumber) << " lines read from " << fileName << '\n';
	file.close();
}
void editDirectives(std::string rainFile)
{
	std::fstream file(rainFile, std::ios::in);
	std::string line = "", newLine;
	std::string newFile = "";

	if (!file) { std::cout << "Couldn't open " << rainFile << '\n'; }
	while (getline(file, line))
	{
		if (line[0] == '#')
		{
			if (programmerString(line)) { newFile += ('#' + line + '\n'); }
			else { newFile += (line + '\n'); }
		}
		else { newFile += (line + '\n'); }
		line = "";
	}
	file.close();
	file.open(rainFile, std::ios::out);
	file << newFile;
	file.close();
}
bool programmerString(std::string& rainString) // allows programmer to modify a string
{                                    // was used to add hash prefixes and year data to govt                       
	std::string user;                // text data
	std::cout << "Current String: \n" << rainString
		<< "\n /end of string\n";
	std::cout << "Change string? Y/n\n";
	getline(std::cin, user);
	if (toupper(user[0]) == 'Y')
	{
		std::cout << "Please enter new string:\n";
		getline(std::cin, rainString);
		return true;
	}
	return false; // returns false if string is not changed
}
void removeSpacesFromLocationNames(std::string rainFile) // govt text came with lots of spaced inside
{                                          // location names which made it difficult to differentiate
	std::fstream file(rainFile, std::ios::in);  // location names from other arguments. Fortunately
	std::string line = "", newLine;           // tabs were used in most other places which made the 
	std::string newFile = "";                 // following functionality rather simple
	int argCount = 0;
	int lineCount = 0;

	while (getline(file, line))
	{
		std::cout << lineCount << '\n';
		//std::cout << "counter: " << argCount << '\n';
		for (size_t i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ') { newLine += '_'; }
			else { newLine += line[i]; }
		}
		newFile += (newLine + "\n");
		++lineCount;
		line = "";
		newLine = "";
	}
	std::cout << newFile;
	file.close();
	file.open(rainFile, std::ios::out);
	file << newFile;
	file.close();
}
void cleanRainFile(std::string rainFile) // used to remove extraneous text data from govt data
{                                        // based on number of arguments per line
	std::fstream file(rainFile, std::ios::in);
	std::string line = "", newLine;
	std::string newFile = "";
	const int MIN_ARGS = 6;
	

	while (getline(file, line))
	{
		if (argCounter(line) >= MIN_ARGS || line[0] == '#') { newFile += (line + "\n"); }
		line = "";
		newLine = "";
	}
	file.close();
	file.open(rainFile, std::ios::out);
	file << newFile;
	file.close();
}
int argCounter(std::string line) // counts potential argument on a given line
{                               // for use in cleaning govt data
	int count = 1;
	bool isArgument = true;
	for (size_t i = 0; i < line.length(); i++)
	{
		if ((line[i] == ' ' || line[i] == '\t') && isArgument)
		{
			isArgument = false;
			++count;
		}
		else if (line[i] != ' ' && line[i] == '\t') { isArgument = true; }
	}
	return count;
}