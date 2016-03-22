#include "AsvUri.h"

unique_ptr<AsvUri> AsvUri::Create(string uri)
{
    unique_ptr<AsvUri> asvUri(new AsvUri);
	auto index = uri.find("://");
    if (index == string::npos || index == 0){
		return NULL;
	}
	
	asvUri->Scheme = uri.substr(0, index);
	asvUri->Path = uri.substr(index+3);
    return asvUri;
} 
