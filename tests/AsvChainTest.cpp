#include "catch.hpp"
#include <memory>
#include "../src/AsvChain.h"

TEST_CASE( "AsvChain works", "[AsvChain]" ) {
    auto state1 = std::make_shared<AsvState>("calc://1");
	state1->Data.push_back(std::make_shared<AsvEntry>("1"));
	state1->Data.push_back(std::make_shared<AsvEntry>("2"));
	    
    auto state2 = std::make_shared<AsvState>("calc://1+2");
	state2->Data.push_back(std::make_shared<AsvEntry>("2"));
	state2->Data.push_back(std::make_shared<AsvEntry>("3"));
	
    auto state3 = std::make_shared<AsvState>("calc3://");
    state3->Data.push_back(std::make_shared<AsvEntry>("2"));
    state3->Data.push_back(std::make_shared<AsvEntry>("3"));

	AsvChain chain;
    chain.Add(state1);
    REQUIRE(chain.Current() == state1);
    // Current -1
    chain.Add(state2);
    REQUIRE(chain.Current() == state2);
	
    chain.Prev();
    REQUIRE(chain.Current() == state1);

    chain.Add(state3);
    REQUIRE(chain.Current() == state3);
}


TEST_CASE( "AsvChain invalid move", "[AsvChain]" ) {
    auto state1 = std::make_shared<AsvState>("calc://1");
    auto state2 = std::make_shared<AsvState>("calc://2");

    AsvChain chain;
    REQUIRE(chain.Current() == nullptr);

    chain.Add(state1);
    REQUIRE(chain.Current() == state1);

    chain.Add(state2);
    REQUIRE_THROWS_WITH(chain.Next(), "Last state reached.");
    REQUIRE(chain.Current() == state2);

    REQUIRE_NOTHROW(chain.Prev());
    REQUIRE(chain.Current() == state1);

    REQUIRE_THROWS_WITH(chain.Prev(), "First state reached.");
    REQUIRE(chain.Current() == state1);
}
