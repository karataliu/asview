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
    AsvState(string uri);
	string Uri;
    string Scheme;
    string Path;
	vector<shared_ptr<AsvEntry>> Data;
};

