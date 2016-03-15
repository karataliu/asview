#include "AsvUri.h"

shared_ptr<AsvUri> AsvUri::Create(string uri)
{
	auto asvUri = std::make_shared<AsvUri>();
	asvUri->Scheme = "calc1";
	asvUri->Path = "a+b";
	 
	return asvUri;
}