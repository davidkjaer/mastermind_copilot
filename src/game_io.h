#pragma once
#include <string>

namespace mastermind
{
    class game_io
    {
        public:
        virtual ~game_io() = default;
        virtual std::string get_next_guess() = 0;
        virtual void show_result(int back, int white) = 0;
        virtual void game_won() = 0;
    };
}