//#pragma once
#include "../AsvState.h"
#include "../AsvScheme.h"

class AsvCalc : public AsvScheme
{
public:
    AsvCalc();
    std::vector<std::shared_ptr<AsvEntry>> Load(std::string path) const;
    std::string Jump(std::string path, std::string id) const;
};
