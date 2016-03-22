#pragma once

#include <memory>
#include <string>
#include <vector>
#include <string>
#include "AsvUri.h"
#include "AsvEntry.h"
#include "AsvScheme.h"
#include "AsvLoader.h"
using namespace std;

class AsvState
{
public:
    AsvState(string uri);
    string Uri;
    unique_ptr<AsvUri> BoundUri;
	vector<shared_ptr<AsvEntry>> Data;
    void Load();
    unique_ptr<AsvState> Load1(size_t index) const;

    static unique_ptr<AsvState> Create(const string& uri, const AsvLoader* loader);

private:
    const AsvScheme* Scheme;
};

