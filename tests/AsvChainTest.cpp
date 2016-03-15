#include <catch.hpp>
#include <memory>
#include "AsvChain.h"

TEST_CASE( "AsvChain works", "[AsvChain]" ) {
	auto state1 = std::make_shared<AsvState>();
	state1->Uri="calc://1";
	state1->Data.push_back(std::make_shared<AsvEntry>("1"));
	state1->Data.push_back(std::make_shared<AsvEntry>("2"));
	
	auto state2 = std::make_shared<AsvState>();
	state2->Uri="calc://1+2";
	state2->Data.push_back(std::make_shared<AsvEntry>("2"));
	state2->Data.push_back(std::make_shared<AsvEntry>("3"));
	
	AsvChain chain;
	chain.Add(state1);
	REQUIRE(chain.Current() == state1);
	
	chain.Add(state2);
	REQUIRE(chain.Current() == state2);
	
	int prev = chain.Prev();
	REQUIRE(prev == 0 );
	REQUIRE(chain.Current() == state1);
}
