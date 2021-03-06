#include "catch.hpp"
#include "AsvState.h"
#include "AsvException.h"
using namespace std;

class Calc3Protocol : public AsvScheme
{
public:
    Calc3Protocol() : AsvScheme("calc3") {}
    vector<shared_ptr<AsvEntry>> Load(string path) const
    {
        throw AsvException("Test data loading error.");
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


TEST_CASE( "AsvEntry works", "[AsvEntry]" ) {
	AsvEntry ae("23");
    REQUIRE( "23" == ae.id );
}


TEST_CASE( "AsvState works", "[AsvState]" ) {
	auto entry1 = std::make_shared<AsvEntry>("1");
	auto entry2 = std::make_shared<AsvEntry>("2");
    AsvState state("calc://1+1");
	state.Data.push_back(entry1);
	state.Data.push_back(entry2);
	
	REQUIRE( state.Uri == "calc://1+1" );
	REQUIRE( state.Data.size() == 2 );
	REQUIRE( state.Data[0] == entry1 );
	REQUIRE( state.Data[1]->id == "2" );

    REQUIRE(state.BoundUri->Scheme == "calc");
    REQUIRE(state.BoundUri->Path == "1+1");
}


TEST_CASE( "AsvState with invalid input", "[AsvState]" ) {
    REQUIRE_THROWS(new AsvState("bz"));
}


TEST_CASE( "Create State", "[AsvState]" ) {
    auto loader = make_shared<AsvLoader>();
    loader->AddScheme(unique_ptr<AsvScheme>(new Calc2Protocol));

    auto s1 = AsvState::Create("calc2://29", loader.get());

    REQUIRE (s1->Uri == "calc2://29");
    auto data = s1->Data;
    REQUIRE (data.size() == 2);
    REQUIRE (data[0]->id == "1");
    REQUIRE (data[1]->id == "2");

    auto s2 = AsvState::Create("calc2://39", loader.get());

    REQUIRE (s2->Uri == "calc2://39");
    data = s2->Data;
    REQUIRE (data.size() == 3);
    REQUIRE (data[0]->id == "1");
    REQUIRE (data[1]->id == "2");
    REQUIRE (data[2]->id == "3");
}


TEST_CASE( "AsvState Load 1 and 2.", "[AsvState]" ) {
    AsvLoader loader;
    loader.AddScheme(unique_ptr<AsvScheme>(new Calc2Protocol));
    auto s1 = AsvState::Create("calc2://49", &loader);
    REQUIRE (s1->Uri == "calc2://49");

    auto s2 = s1->Load1(1);
    REQUIRE (s2->Uri == "calc2://49+2");
}

TEST_CASE( "AsvState invalid.", "[AsvState]" ) {
    AsvLoader loader;
    loader.AddScheme(unique_ptr<AsvScheme>(new Calc2Protocol));
    loader.AddScheme(unique_ptr<AsvScheme>(new Calc3Protocol));
    REQUIRE_THROWS_WITH(AsvState::Create("calc1://49", &loader), "scheme null");
    REQUIRE_THROWS_WITH(AsvState::Create("://49", &loader), "Malformat Uri.");
    REQUIRE_THROWS_WITH(AsvState::Create("calc3://49", &loader), "Test data loading error.");
}



