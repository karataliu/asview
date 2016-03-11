#pragma once

#include <string>
#include <vector>
using namespace std;

class AsvEntry
{
public:
	int index;
};

class AsvState
{
public:
	string Uri;
	vector<AsvEntry> Data;
};

