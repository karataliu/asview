#include <catch.hpp>
#include <memory>
#include "AsvLoader.h"

template <typename T>
class Singleton
{
    Singleton(){};
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
    static T* Instance()
    {
        static T instance;
        return &instance;
    }
};


class Calc1Protocol : public AsvProtocol
{
public:
    Calc1Protocol() : AsvProtocol("calc1") {}
};

class Calc2Protocol : public AsvProtocol
{
public:
    Calc2Protocol() : AsvProtocol("calc2") {}
    void go();
};


TEST_CASE( "AsvLoader works", "[AsvLoader]" ) {
	auto loader = AsvLoader::Instance;
    REQUIRE ( loader->GetProtocol("calc1") == NULL);
    REQUIRE ( loader->GetProtocol("calc2") == NULL);
    REQUIRE ( loader->GetProtocol("http") == NULL);
    
    auto p1 = Singleton<Calc1Protocol>::Instance();
    loader->AddProtocol(p1);
    REQUIRE ( loader->GetProtocol("calc1") == p1);
    REQUIRE ( loader->GetProtocol("calc2") == NULL);
    REQUIRE ( loader->GetProtocol("http") == NULL);
    
    auto p2 = Singleton<Calc2Protocol>::Instance();
    loader->AddProtocol(p2);
    REQUIRE ( loader->GetProtocol("calc1") == p1);
    REQUIRE ( loader->GetProtocol("calc2") == p2);
    REQUIRE ( loader->GetProtocol("http") == NULL);
}
