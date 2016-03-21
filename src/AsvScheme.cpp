#include "AsvScheme.h"

AsvScheme::AsvScheme(string scheme) : scheme(scheme) {}

bool AsvScheme::CanHandle(string name)
{
    return name == scheme;
}

vector<shared_ptr<AsvEntry>> AsvScheme::Load(string path) const
{
    vector<shared_ptr<AsvEntry>> data;
    return data;
}

string AsvScheme::Jump(string path, string id) const
{
    return path + "/" + id;
}
