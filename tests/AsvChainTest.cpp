#include "catch.hpp"
#include <memory>
#include "../src/AsvChain.h"

TEST_CASE( "AsvChain works", "[AsvChain]" ) {
    auto state1 = new AsvState("calc://1");
	state1->Data.push_back(std::make_shared<AsvEntry>("1"));
	state1->Data.push_back(std::make_shared<AsvEntry>("2"));
	    
    auto state2 = new AsvState("calc://1+2");
	state2->Data.push_back(std::make_shared<AsvEntry>("2"));
	state2->Data.push_back(std::make_shared<AsvEntry>("3"));
	
    auto state3 = new AsvState("calc3://");
    state3->Data.push_back(std::make_shared<AsvEntry>("2"));
    state3->Data.push_back(std::make_shared<AsvEntry>("3"));

	AsvChain chain;
    chain.Add(state1);
    REQUIRE(chain.Current() == state1);
    // Current -1
    chain.Add(state2);
    REQUIRE(chain.Current() == state2);
	
	int prev = chain.Prev();
    REQUIRE(prev == 1);
    REQUIRE(chain.Current() == state1);

    chain.Add(state3);
    REQUIRE(chain.Current() == state3);
}
