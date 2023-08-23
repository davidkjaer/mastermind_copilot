#define GTEST_MAIN
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "game_io.h"
#include "game.h"

using namespace testing;

namespace mastermind::unit_test
{
    class mock_io : public game_io
    {
        public:
        MOCK_METHOD(std::string, get_next_guess, (), (override));
        MOCK_METHOD(void, show_result, (int, int), (override));
        MOCK_METHOD(void, game_won, (), (override));
    };

    TEST(game, run_game_bad_guess)
    {
        mock_io io;
        EXPECT_CALL(io, get_next_guess())
            .WillOnce(Return("RRRRR"))
            .WillOnce(Return(""));
        EXPECT_CALL(io, show_result(0, 0));
        run_game(io, "GGGGG");
    }

    TEST(game, run_game_perfect_first_guess)
    {
        mock_io io;
        EXPECT_CALL(io, get_next_guess())
            .WillOnce(Return("GGGGG"));
        EXPECT_CALL(io, game_won());
        run_game(io, "GGGGG");
    }

    TEST(game, run_game_perfect_second_guess)
    {
        mock_io io;
        EXPECT_CALL(io, get_next_guess())
            .WillOnce(Return("RRRRR"))
            .WillOnce(Return("GGGGG"));
        EXPECT_CALL(io, game_won());
        EXPECT_CALL(io, show_result(0, 0));
        run_game(io, "GGGGG");
    }

    TEST(game, run_game_partially_correct_guesses)
    {
        mock_io io;
        EXPECT_CALL(io, get_next_guess())
            .WillOnce(Return("RRRRR"))
            .WillOnce(Return("GYRPO"))
            .WillOnce(Return("RGPYO"))
            .WillOnce(Return(""));

        EXPECT_CALL(io, show_result(1, 0));
        EXPECT_CALL(io, show_result(0, 5));
        EXPECT_CALL(io, show_result(2, 3));
        run_game(io, "RGYOP");
    }
}