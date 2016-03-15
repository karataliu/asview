#pragma once

#include <memory>
#include <string>
#include <vector>
#include <string>
using namespace std;

class AsvEntry
{
public:
	AsvEntry(string id);
	string id;
};

class AsvState
{
public:
	string Uri;
	vector<shared_ptr<AsvEntry>> Data;
};

