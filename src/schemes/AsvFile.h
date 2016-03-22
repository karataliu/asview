#pragma once

#include "../AsvScheme.h"

class AsvFile : public AsvScheme
{
public:
    AsvFile();
    std::vector<std::shared_ptr<AsvEntry>> Load(std::string path) const;
};
