#pragma once
#ifndef RAIN_HASH_H
#define RAIN_HASH_H
#include <iostream>
#include "AnyArray.h"

// Zenyn Ethridge, Jesse Orozco, Geremias Montano-Izazaga

// hash table for strings, intended use is to allow
// rapid lookup to check if a location ID already exists
// in a LocationArray object. All strings should be unique,
// even if integer member is different. RainHash should not
// accept insertions where a particular string already exists

enum State { fresh = 0, inUse, used };
struct StrNum {
	std::string str; // represents an ID, date, or other
	int num = 0; // represents an index inside an array
};
class RainHash {
private:
	int size;
	AnyArray<StrNum> table;
	AnyArray<State> states;
	const StrNum nullVal = { "", -1 }; // -1 is never an index
public:
	RainHash(int);
	int hash(std::string);
	int hash(StrNum x) { return hash(x.str); }
	int getNum(std::string);
	void insert(StrNum);
	void remove(std::string);
	int search(std::string);
	bool exists(std::string str) { return (search(str) >= 0); }
	static bool existsUnitTest();
	static void runAllTests();
};
#endif // !RAIN_HASH_H
