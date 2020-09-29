#pragma once
#include <string>
//#include "Entry.h"
using namespace std;

class Comparator
{
public:
	// comparator handles diff data types
	typedef Entry<int, string> x;
	typedef Entry<string, int> y;

	bool operator()(x a, x b)	// compares key int
	{
		return a.key() < b.key();
	}
	bool operator()(y a, y b)	// compares value int
	{
		return a.value() < b.value();
	}

};

