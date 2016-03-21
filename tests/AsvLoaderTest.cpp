#include "catch.hpp"
#include <memory>
#include "AsvLoader.h"
#include "AsvLoaderFactory.h"

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
        vector<shared_ptr<AsvEntry>> Load(string path) const
	{
		vector<shared_ptr<AsvEntry>> data;
		return data;
	}
};

class Calc2Protocol : public AsvScheme
{
public:
    Calc2Protocol() : AsvScheme("calc2") {}
    vector<shared_ptr<AsvEntry>> Load(string path) const
	{
		vector<shared_ptr<AsvEntry>> data;
        int cou = path[0] - '0';
        for(int i=1;i<=cou;i++)
            data.push_back(make_shared<AsvEntry>(to_string(i)));

		return data;
	}

    string Jump(string path, string id) const
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

    //auto s1 = unique_ptr<AsvState>(new AsvState("calc2://29"));
    //loader->Load(s1.get());
    // auto s1 = loader->CreateState("calc2://29");
    auto s1 = CreateState("calc2://29", loader.get());

    loader->Load(s1);
    REQUIRE (s1->Uri == "calc2://29");
    auto data = s1->Data;
    REQUIRE (data.size() == 2);
    REQUIRE (data[0]->id == "1");
    REQUIRE (data[1]->id == "2");

    //auto s2 = unique_ptr<AsvState>(new AsvState("calc2://39"));
    //loader->Load(s2.get());
    // auto s2 = loader->CreateState("calc2://39");
    auto s2 = CreateState("calc2://39", loader.get());

    loader->Load(s2);
    REQUIRE (s2->Uri == "calc2://39");
    data = s2->Data;
    REQUIRE (data.size() == 3);
    REQUIRE (data[0]->id == "1");
    REQUIRE (data[1]->id == "2");
    REQUIRE (data[2]->id == "3");
}


TEST_CASE( "AsvLoader Load with jump", "[AsvLoader]" ) {
    //auto loader = make_shared<AsvLoader>();
    //loader->AddProtocol(Singleton<Calc2Protocol>::Instance());
    AsvLoader loader;
    loader.AddProtocol(Singleton<Calc2Protocol>::Instance());
    // auto s1 = unique_ptr<AsvState>(new AsvState("calc2://49"));
    // loader->Load(s1.get());
    //auto s1 = loader->CreateState("calc2://49");
    auto s1 = CreateState("calc2://49", &loader);

    loader.Load(s1);
    REQUIRE (s1->Uri == "calc2://49");

    auto s2 = s1->Load1(1);
    REQUIRE (s2->Uri == "calc2://49+2");

}
