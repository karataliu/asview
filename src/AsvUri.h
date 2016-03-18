#pragma once

#include <string>
#include <memory>
using namespace std;

class AsvUri
{
public:
	string Scheme;
	string Path;
    static unique_ptr<AsvUri> Create(string Uri);
};
