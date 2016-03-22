#include <memory>
#include "catch.hpp"
#include "AsvUri.h"
#include "AsvException.h"
using namespace std;

TEST_CASE( "AsvUri works", "[AsvUri]" ) {
	auto a = AsvUri::Create("calc1://a+b");
    unique_ptr<AsvUri> null = NULL;
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

    REQUIRE_THROWS_AS (AsvUri::Create("calc2:/3+5"), AsvException);
    REQUIRE_THROWS (AsvUri::Create("://b") == nullptr);
    REQUIRE_THROWS (AsvUri::Create("://") == nullptr);
}
