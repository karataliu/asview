#include "catch.hpp"
#include <memory>
#include "AsvLoader.h"
#include "AsvState.h"
using namespace std;

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


struct Calc1Protocol : public AsvScheme
{
    Calc1Protocol() : AsvScheme("calc1") {}
};

struct Calc2Protocol : public AsvScheme
{
    Calc2Protocol() : AsvScheme("calc2") {}
};


TEST_CASE( "AsvLoader GetProtocol", "[AsvLoader]" ) {
    auto loader = make_shared<AsvLoader>();
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
