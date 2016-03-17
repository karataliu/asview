#include "catch.hpp"
#include "AsvState.h"

TEST_CASE( "AsvEntry works", "[AsvEntry]" ) {
	AsvEntry ae("23");
    REQUIRE( "23" == ae.id );
}


TEST_CASE( "AsvState works", "[AsvState]" ) {
	auto entry1 = std::make_shared<AsvEntry>("1");
	auto entry2 = std::make_shared<AsvEntry>("2");
	AsvState state;
	state.Uri="calc://1+1";
	state.Data.push_back(entry1);
	state.Data.push_back(entry2);
	
	REQUIRE( state.Uri == "calc://1+1" );
	REQUIRE( state.Data.size() == 2 );
	REQUIRE( state.Data[0] == entry1 );
	REQUIRE( state.Data[1]->id == "2" );
}
