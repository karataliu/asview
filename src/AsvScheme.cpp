#include "AsvScheme.h"

AsvScheme::AsvScheme(string scheme) : scheme(scheme) {}

bool AsvScheme::CanHandle(string name)
{
    return name == scheme;
}

string AsvScheme::Jump(string path, string id)
{
    return path + "/" + id;
}
