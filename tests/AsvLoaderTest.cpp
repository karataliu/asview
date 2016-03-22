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
    AsvLoader loader;
    REQUIRE ( loader.GetScheme("calc1") == NULL);
    REQUIRE ( loader.GetScheme("calc2") == NULL);
    REQUIRE ( loader.GetScheme("http") == NULL);
    
    auto p1 = Singleton<Calc1Protocol>::Instance();
    loader.AddScheme(p1);
    REQUIRE (loader.GetScheme("calc1") == p1);
    REQUIRE (loader.GetScheme("calc2") == NULL);
    REQUIRE (loader.GetScheme("http") == NULL);
    
    auto p2 = Singleton<Calc2Protocol>::Instance();
    loader.AddScheme(p2);
    REQUIRE (loader.GetScheme("calc1") == p1);
    REQUIRE (loader.GetScheme("calc2") == p2);
    REQUIRE (loader.GetScheme("http") == NULL);
}
