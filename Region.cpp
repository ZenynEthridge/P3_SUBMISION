#include "Region.h"

Region::Region() :AnyArray()
{
	ID = -1;
	name = "";
}
Region::Region(std::string str) : AnyArray()
{
	ID = -1;
	name = str;
}