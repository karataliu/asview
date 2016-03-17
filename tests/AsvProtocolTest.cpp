#include <catch.hpp>
#include <memory>
#include <iostream>
#include "AsvLoader.h"

class CalcProtocol : public AsvProtocol
{
public:
    CalcProtocol() : AsvProtocol("calc2") {}
	vector<shared_ptr<AsvEntry>> Load(string path)
	{
		vector<shared_ptr<AsvEntry>> data;
		int val =0;
		try{
			val = stoi(path);
		}catch (const invalid_argument& ia){
			return data;
		}
		
		data.push_back(make_shared<AsvEntry>(to_string(val+1)));
		data.push_back(make_shared<AsvEntry>(to_string(val+2)));
		return data;
	}
};


TEST_CASE("AsvProtocol works", "[AsvProtocol]" ) {
	CalcProtocol calc1;
	auto data = calc1.Load("32");
	REQUIRE(data.size() == 2);
    REQUIRE(data[0]->id == "33");
	REQUIRE(data[1]->id == "34");
}

TEST_CASE("AsvProtocol for invalid path", "[AsvProtocol]" ) {
	CalcProtocol calc2;
	auto data = calc2.Load("a");
	REQUIRE(data.size() == 0);
}


TEST_CASE("AsvProtocol for jump", "[AsvProtocol]" ) {
    CalcProtocol calc2;
    string str = calc2.Jump("a", "1");
    REQUIRE(str == "a/1");
}
