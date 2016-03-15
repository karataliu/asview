#include <unittest++/UnitTest++.h>
#include "AsvState.h"

SUITE(AsvStateTest)
{
    TEST(TestEntry)
    {
		AsvEntry ae("2");

		CHECK_EQUAL("23", ae.id);
    }
}


