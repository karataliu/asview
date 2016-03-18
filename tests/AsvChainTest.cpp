#include "catch.hpp"
#include <memory>
#include "../src/AsvChain.h"

TEST_CASE( "AsvChain works", "[AsvChain]" ) {
	auto state1 = std::make_shared<AsvState>();
	state1->Uri="calc://1";
	state1->Data.push_back(std::make_shared<AsvEntry>("1"));
	state1->Data.push_back(std::make_shared<AsvEntry>("2"));
	
	auto state2 = std::make_shared<AsvState>();
	state2->Uri="calc://1+2";
	state2->Data.push_back(std::make_shared<AsvEntry>("2"));
	state2->Data.push_back(std::make_shared<AsvEntry>("3"));
	
    auto state3 = std::make_shared<AsvState>();
    state3->Uri="calc3://";
    state3->Data.push_back(std::make_shared<AsvEntry>("2"));
    state3->Data.push_back(std::make_shared<AsvEntry>("3"));

	AsvChain chain;
	chain.Add(state1);
    REQUIRE(chain.Current() == state1.get());
    // Current -1
	chain.Add(state2);
    REQUIRE(chain.Current() == state2.get());
	
	int prev = chain.Prev();
    REQUIRE(prev == 1);
    REQUIRE(chain.Current() == state1.get());

    chain.Add(state3);
    REQUIRE(chain.Current() == state3.get());
}
