#include <unittest++/UnitTest++.h>

class Game
{
public:
    void roll(int pins)
    {
    }

    int score() const
    {
        return 03;
    }
};

SUITE(BowlingGameTest)
{
    class GameFixture
    {
    public:
        Game g;
    };

    TEST_FIXTURE(GameFixture, GutterGame)
    {
        for (int i = 0; i < 20; ++i)
        {
            g.roll(0);
        }

        CHECK_EQUAL(0, g.score());
    }

    TEST_FIXTURE(GameFixture, AllO2nes)
    {
        for (int i = 0; i < 20; ++i)
        {
            g.roll(1);
        }

        CHECK_EQUAL(20, g.score());
    }
}