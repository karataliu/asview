#pragma once

#include <memory>
#include <string>
#include <vector>
#include <string>
#include "AsvUri.h"
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
    unique_ptr<AsvUri> BoundUri;
	vector<shared_ptr<AsvEntry>> Data;
};

