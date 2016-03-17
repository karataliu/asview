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


class Calc1Protocol : public AsvScheme
{
public:
    Calc1Protocol() : AsvScheme("calc1") {}
        vector<shared_ptr<AsvEntry>> Load(string path)
	{
		vector<shared_ptr<AsvEntry>> data;
		return data;
	}
};

class Calc2Protocol : public AsvScheme
{
public:
    Calc2Protocol() : AsvScheme("calc2") {}
    vector<shared_ptr<AsvEntry>> Load(string path)
	{
		vector<shared_ptr<AsvEntry>> data;
        int cou = path[0] - '0';
        for(int i=1;i<=cou;i++)
            data.push_back(make_shared<AsvEntry>(to_string(i)));

		return data;
	}

    string Jump(string path, string id)
    {
        return path + "+" + id;
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

    state = loader->Load("calc2://39");
    REQUIRE (state->Uri == "calc2://39");
    data = state->Data;
    REQUIRE (data.size() == 3);
    REQUIRE (data[0]->id == "1");
    REQUIRE (data[1]->id == "2");
    REQUIRE (data[2]->id == "3");
}


TEST_CASE( "AsvLoader Load with jump", "[AsvLoader]" ) {
    auto loader = make_shared<AsvLoader>();
    loader->AddProtocol(Singleton<Calc2Protocol>::Instance());
    auto state = loader->Load("calc2://49");
    REQUIRE (state->Uri == "calc2://49");

    state = loader->Load(state, 1);
    REQUIRE (state->Uri == "calc2://49+2");

}
