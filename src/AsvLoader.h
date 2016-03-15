// Loader with protocol
#include <memory>
#include <list>
using namespace std;

class AsvProtocol
{
public:
	virtual bool CanHandle(string name) = 0;
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

