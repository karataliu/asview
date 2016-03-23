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
    REQUIRE ( loader.GetScheme("calc1") == nullptr);
    REQUIRE ( loader.GetScheme("calc2") == nullptr);
    REQUIRE ( loader.GetScheme("http") == nullptr);
    
    auto p1 = new Calc1Protocol;
    loader.AddScheme(unique_ptr<AsvScheme>(p1));
    REQUIRE (loader.GetScheme("calc1").get() == p1);
    REQUIRE (loader.GetScheme("calc2") == nullptr);
    REQUIRE (loader.GetScheme("http") == nullptr);
    
    auto p2 = new Calc2Protocol;
    loader.AddScheme(unique_ptr<AsvScheme>(p2));
    REQUIRE (loader.GetScheme("calc1").get() == p1);
    REQUIRE (loader.GetScheme("calc2").get() == p2);
    REQUIRE (loader.GetScheme("http") == nullptr);
}
