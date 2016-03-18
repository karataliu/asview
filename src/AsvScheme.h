#pragma once

#include <vector>
#include <memory>
#include <list>
#include "AsvEntry.h"
using namespace std;

class AsvScheme
{
public:
    AsvScheme(string scheme);
    bool CanHandle(string name);
    virtual vector<shared_ptr<AsvEntry>> Load(string path) const = 0;
    virtual string Jump(string path, string id) const;
private:
    string scheme;
};
