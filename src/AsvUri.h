#pragma once

#include <string>
#include <memory>

class AsvUri
{
public:
    std::string Scheme;
    std::string Path;
    static std::unique_ptr<AsvUri> Create(std::string Uri);
};
