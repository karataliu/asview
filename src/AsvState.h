#pragma once

#include <memory>
#include <string>
#include <vector>
#include <string>
#include "AsvUri.h"
#include "AsvEntry.h"
#include "AsvScheme.h"
using namespace std;

class AsvState
{
public:
    AsvState(string uri);
    string Uri;
    unique_ptr<AsvUri> BoundUri;
    const AsvScheme* Scheme;
	vector<shared_ptr<AsvEntry>> Data;
};

