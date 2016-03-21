#pragma once

#include <vector>
#include <memory>
#include "AsvEntry.h"
using namespace std;

class AsvScheme
{
public:
    AsvScheme(string scheme);
    bool CanHandle(string name);
    virtual vector<shared_ptr<AsvEntry>> Load(string path) const;
    virtual string Jump(string path, string id) const;
private:
    string scheme;
};
