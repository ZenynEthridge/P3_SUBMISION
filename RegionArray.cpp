#include "RegionArray.h"

void RegionArray::printEverything()
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << arr[i].getName() << '\n';
	}
}
void RegionArray::pushback(std::string str)
{
	if (str.empty()) { return; }
	Region reg(str); // creates region from str
	AnyArray::pushback(reg); // normal push back
}
void RegionArray::pushback(Location* loc)
{ // overrides AnyArray::pushback
	if (loc->getRegion().empty()) { return; } // skip if no region
	int i = findRegion(loc->getRegion()); // find the region
	if (i >= 0) { atReference(i)->pushback(loc); } else
	{
		pushback(loc->getRegion());
		atReference(size - 1)->pushback(loc);
	}
}
bool RegionArray::hasRegion(Region reg)
{ // checks if region already exists
	for (size_t i = 0; i < size; i++)
	{
		if (reg == arr[i]) { return true; }
	}
	return false;
}
int RegionArray::findRegion(std::string reg)
{ // finds region index from string
	for (int i = 0; i < size; i++)
	{
		if (reg == at(i).getName()) { return i; }
	}
	return -1;
}