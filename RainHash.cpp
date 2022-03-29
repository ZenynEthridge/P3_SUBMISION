#include "RainHash.h"

RainHash::RainHash(int n) : size(n)
{
	for (size_t i = 0; i < size; i++)
	{
		table.pushback(nullVal);
		states.pushback(fresh);
	}
}
int RainHash::hash(std::string str)
{
	int n = 0, i = 2;
	for (char c : str) { n += (int(c) * i++); }
	if (!n) { return 0; } // avoid /0 error
	return n % size;
}
void RainHash::insert(StrNum x)
{
	int n = hash(x.str);
	int start = n;
	while (states.at(n) == inUse && table.at(n).str != x.str)
	{
		n++;
		if (n == size) { n = 0; }
		if (n == start) { return; }
	}
	if (table.at(n).str == x.str)
	{
		std::cout << x.str << " already exists!\n";
		return;
	}
	table.set(x, n);
	states.set(inUse, n);
}
int RainHash::search(std::string str)
{
	int n = hash(str);
	int start = n;
	while (states.at(n) != fresh)
	{
		if (table.at(n).str == str) { return n; }
		n++;
		if (n == size) { n = 0; }
		if (n == start) { return -1; }
	}
	return -1;
}
void RainHash::runAllTests()
{
	std::cout << "Testing rain hash...\n";
	if (!existsUnitTest())
	{
		std::cout << "Failed!\n";
		return;
	}
	std::cout << "Passed!\n";
}
void RainHash::remove(std::string str)
{
	int num = search(str);
	if (num >= 0)
	{
		table.set(nullVal, num);
		states.set(used, num);
	}
}
bool RainHash::existsUnitTest()
{
	RainHash hash(100);
	std::string stringSet[] = 
	{
		"dog","cat","cat","bird","lizard","cow","person", "snake" 
	};
	std::string testSet[] = { "cow","frog", "person","snake" };
	bool keySet[] = { true,false,true,false };
	int i = 0;
	for (std::string s : stringSet) { hash.insert({ s, 0 }); }
	hash.remove("snake");
	for (std::string s : testSet)
	{
		if (hash.exists(s) != keySet[i++])
		{
			std::cout << s << '\n';
			return false;
		}
	}
	return true;
}
int RainHash::getNum(std::string str)
{
	int n = search(str);
	if (n >= 0) { return table.at(n).num; } else { return -1; }
}