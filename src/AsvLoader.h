// Loader with protocol
#include <vector>
#include <memory>
#include <list>
#include "AsvState.h"
using namespace std;

class AsvProtocol
{
public:
	AsvProtocol(string scheme);
	bool CanHandle(string name);
	vector<shared_ptr<AsvEntry>> Load(string path);
private:
	string scheme;
};

class AsvLoader
{
public:
	static AsvLoader* Instance;
	// shared_ptr<AsvState> Load(string Uri);
	AsvProtocol* GetProtocol(string name);
	void AddProtocol(AsvProtocol* protocol);
private:
	AsvLoader(){}
	AsvLoader(const AsvLoader&) = delete;
	AsvLoader& operator=(const AsvLoader&) = delete;
	list<AsvProtocol*> protocolList;
};

