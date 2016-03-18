//#pragma once
#include "../AsvState.h"
#include "../AsvScheme.h"

class AsvCalc : public AsvScheme
{
public:
    AsvCalc();
    vector<shared_ptr<AsvEntry>> Load(string path) const;
    string Jump(string path, string id) const;
};
