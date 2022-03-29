#pragma once
#ifndef TEXTFILESTUFF_H
#define TEXTFILESTUFF_H
#include <iostream>
#include <string>
#include <fstream>
#include "LocationArray.h"
#include "Region.h"

// Zenyn Ethridge, Jesse Orozco, Geremias Montano-Izazaga

// |!| Singleton class, all members should be marked static





// |!| Intended for programmer use, not user use
// everything in this file was used to interpret data copy pasted
// from govt source website. most of it was intended for one time
// use and is not a part of current functionality
void cleanRainFile(std::string);
int argCounter(std::string);
bool programmerString(std::string &);
void editDirectives(std::string);
void initializeLocations(std::string, LocationArray&);
void readHashes(std::string, std::string &, int &);
void removeSpacesFromLocationNames(std::string rainFile);


#endif