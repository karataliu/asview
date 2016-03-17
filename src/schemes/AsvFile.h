//#pragma once
#include "../AsvState.h"
#include "../AsvScheme.h"

class AsvFile : public AsvScheme
{
public:
    AsvFile();
    vector<shared_ptr<AsvEntry>> Load(string path);
};
