#pragma once

#include <vector>
#include <memory>
#include "AsvEntry.h"

class AsvScheme
{
public:
    AsvScheme(std::string scheme);
    bool CanHandle(std::string name);
    virtual std::vector<std::shared_ptr<AsvEntry>> Load(std::string path) const;
    virtual std::string Jump(std::string path, std::string id) const;
private:
    std::string scheme;
};
