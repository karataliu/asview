#include <catch.hpp>
#include <memory>
#include "AsvLoader.h"

template <typename T>
class Singleton
{
    Singleton(){};
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
    static T* Instance()
    {
        static T instance;
        return &instance;
    }
};


class Calc1Protocol : public AsvProtocol
{
public:
    Calc1Protocol() : AsvProtocol("calc1") {}
        vector<shared_ptr<AsvEntry>> Load(string path)
	{
		vector<shared_ptr<AsvEntry>> data;
		return data;
	}
};

class Calc2Protocol : public AsvProtocol
{
public:
    Calc2Protocol() : AsvProtocol("calc2") {}
    vector<shared_ptr<AsvEntry>> Load(string path)
	{
		vector<shared_ptr<AsvEntry>> data;
		data.push_back(make_shared<AsvEntry>("1"));
		data.push_back(make_shared<AsvEntry>("2"));
		return data;
	}
};


TEST_CASE( "AsvLoader GetProtocol", "[AsvLoader]" ) {
	auto loader = make_shared<AsvLoader>();
    REQUIRE ( loader->GetProtocol("calc1") == NULL);
    REQUIRE ( loader->GetProtocol("calc2") == NULL);
    REQUIRE ( loader->GetProtocol("http") == NULL);
    
    auto p1 = Singleton<Calc1Protocol>::Instance();
    loader->AddProtocol(p1);
    REQUIRE ( loader->GetProtocol("calc1") == p1);
    REQUIRE ( loader->GetProtocol("calc2") == NULL);
    REQUIRE ( loader->GetProtocol("http") == NULL);
    
    auto p2 = Singleton<Calc2Protocol>::Instance();
    loader->AddProtocol(p2);
    REQUIRE ( loader->GetProtocol("calc1") == p1);
    REQUIRE ( loader->GetProtocol("calc2") == p2);
    REQUIRE ( loader->GetProtocol("http") == NULL);
}


TEST_CASE( "AsvLoader Load", "[AsvLoader]" ) {
	auto loader = make_shared<AsvLoader>();
    loader->AddProtocol(Singleton<Calc2Protocol>::Instance());
    auto state = loader->Load("calc2://29");
    
    REQUIRE (state->Uri == "calc2://29");
    auto data = state->Data;
    REQUIRE (data.size() == 2);
    REQUIRE (data[0]->id == "1");
    REQUIRE (data[1]->id == "2");
}
