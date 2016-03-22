#pragma once

#include <memory>
#include <string>
#include <vector>
#include <string>
#include "AsvUri.h"
#include "AsvEntry.h"
#include "AsvScheme.h"
#include "AsvLoader.h"

class AsvState
{
public:
    AsvState(std::string uri);
    std::string Uri;
    std::unique_ptr<AsvUri> BoundUri;
    std::vector<std::shared_ptr<AsvEntry>> Data;

    std::unique_ptr<AsvState> Load1(std::size_t index) const;
    static std::unique_ptr<AsvState> Create(const std::string& uri, const AsvLoader* loader);

private:
    void Load();
    const AsvScheme* Scheme;
};

