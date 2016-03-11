#include <memory>
#include <unittest++/UnitTest++.h>
#include "AsvChain.h"


SUITE(AsvChainTest)
{
    class AsvChainFixture
    {
    public:
        AsvChain c1;
    };

    TEST_FIXTURE(AsvChainFixture, Test1)
    {
        auto a = std::make_shared<AsvState>();
        c1.Add(a);
        
		CHECK_EQUAL(2, c1.Prev());
    }
}