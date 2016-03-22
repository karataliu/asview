#include <memory>
#include <iostream>
#include <stdexcept>
#include "catch.hpp"
#include "AsvScheme.h"
using namespace std;

class CalcScheme : public AsvScheme
{
public:
    CalcScheme() : AsvScheme("calc2") {}
    vector<shared_ptr<AsvEntry>> Load(string path) const
	{
		vector<shared_ptr<AsvEntry>> data;
		int val =0;
		try{
			val = stoi(path);
        }catch (const std::invalid_argument& ia){
			return data;
		}
		
		data.push_back(make_shared<AsvEntry>(to_string(val+1)));
		data.push_back(make_shared<AsvEntry>(to_string(val+2)));
		return data;
	}
};

TEST_CASE("AsvScheme works", "[AsvScheme]" ) {
    CalcScheme calc1;
	auto data = calc1.Load("32");
	REQUIRE(data.size() == 2);
    REQUIRE(data[0]->id == "33");
	REQUIRE(data[1]->id == "34");
}

TEST_CASE("AsvScheme for invalid path", "[AsvScheme]" ) {
    CalcScheme calc2;
	auto data = calc2.Load("a");
	REQUIRE(data.size() == 0);
}


TEST_CASE("AsvScheme for jump", "[AsvScheme]" ) {
    CalcScheme calc2;
    string str = calc2.Jump("a", "1");
    REQUIRE(str == "a/1");
}
