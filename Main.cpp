#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "UserInterpeter.h"
#include "Sorting.h"

// Zenyn, Jess, Germemias

int main() { UI::run(); }

/*		//READ ME//
*	Project 2 Corrections
* 1. Fixed amount of rows shown, modification made in OuputSetting.h
* 2. All classes should have descriptors now
* 3. Fixed data sorting issues and search issues. Arrays are now sorted
*	 after any user made deletions or additions (of location objects) to location array
* 
*	Project 3 Requirements
* Search implemented in multiple places in UI and LocationArray. UI::findForEdit()
* is probably the best example. You can search by any single letter or an initial substring,
* and a selection menu containing every location ID with that initial letter or substring
* will be presented to choose from
* 
* 
* Sort is implemented in multiple locations in Location array. There is also a
* function (void UI::searchSortDemo) that demonstrates the differences in 
* selection sort, bubble sort and quick sort, and reports the time complexities 
* of these sort types (enter T at user interface to demo)
*/