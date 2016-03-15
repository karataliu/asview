#include <catch.hpp>
#include <memory>
#include "AsvUri.h"

TEST_CASE( "AsvUri works", "[AsvUri]" ) {
	auto a = AsvUri::Create("calc1://a+b");
	
	// REQUIRE( a != std::nullptr );
	REQUIRE( a->Scheme == "calc1" );
	REQUIRE( a->Path == "a+b" );
}
