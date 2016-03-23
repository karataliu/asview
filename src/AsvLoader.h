#pragma once

#include <list>
#include <memory>
#include "AsvScheme.h"

class AsvLoader
{
public:
    std::shared_ptr<AsvScheme> GetScheme(std::string schemeName) const;
    void AddScheme(std::unique_ptr<AsvScheme> scheme);
private:
    std::list<std::shared_ptr<AsvScheme>> protocolList;
};

