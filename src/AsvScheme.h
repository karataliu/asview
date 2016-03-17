#pragma once

#include <vector>
#include <memory>
#include <list>
#include "AsvState.h"
using namespace std;

class AsvScheme
{
public:
    AsvScheme(string scheme);
    bool CanHandle(string name);
    virtual vector<shared_ptr<AsvEntry>> Load(string path) = 0;
    virtual string Jump(string path, string id);
private:
    string scheme;
};
