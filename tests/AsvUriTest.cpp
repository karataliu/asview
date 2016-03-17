#include <catch.hpp>
#include <memory>
#include "AsvUri.h"

TEST_CASE( "AsvUri works", "[AsvUri]" ) {
	auto a = AsvUri::Create("calc1://a+b");
	shared_ptr<AsvUri> null = NULL;
	REQUIRE( a != null );
	REQUIRE( a->Scheme == "calc1" );
	REQUIRE( a->Path == "a+b" );
	
	auto b = AsvUri::Create("calc2://3+5");
	REQUIRE( b != null );
	REQUIRE( b->Scheme == "calc2" );
	REQUIRE( b->Path == "3+5" );

    auto c = AsvUri::Create("a://");
    REQUIRE(c != null);
    REQUIRE(c->Scheme == "a");
    REQUIRE(c->Path == "");
}

TEST_CASE( "AsvUri parse from invalid string should fail", "[AsvUri]" ) {
	shared_ptr<AsvUri> null = NULL;
	REQUIRE ( AsvUri::Create("calc2:/3+5") == null );
	REQUIRE ( AsvUri::Create("://b") == null );
	REQUIRE ( AsvUri::Create("://") == null );
}
