#include <string>
#include <memory>
using namespace std;

class AsvUri
{
public:
	string Scheme;
	string Path;
	static shared_ptr<AsvUri> Create(string Uri);
};