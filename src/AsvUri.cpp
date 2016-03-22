#include "AsvUri.h"

std::unique_ptr<AsvUri> AsvUri::Create(std::string uri)
{
    std::unique_ptr<AsvUri> asvUri(new AsvUri);
	auto index = uri.find("://");
    if (index == std::string::npos || index == 0){
		return NULL;
	}
	
	asvUri->Scheme = uri.substr(0, index);
	asvUri->Path = uri.substr(index+3);
    return asvUri;
} 
