#include <string>
#include <random>
#include <iostream>
#include <array>
#include "game_io.h"
#include "game.h"

using namespace std::literals;
using namespace mastermind;

namespace
{
std::string get_random_code()
{
    const std::string colors = "RGBYOP"s;
    constexpr int length = 5;
    std::string code;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, colors.size() - 1);
    for (int i = 0; i < length; ++i)
    {
        code += std::to_string(colors[dis(gen)]);
    }
    return code;
}
}

class concrete_io : public game_io
{
    public:
    std::string get_next_guess() override
    {
        std::cout << "Please enter your guess:\n";
        std::string guess;
        std::cin >> guess;
        return guess;
    }
    
    void show_result(int black, int white) override
    {
        std::cout << "Result: " << black << " black, " << white << " white\n";
    }

    void game_won() override
    {
        std::cout << "You won!\n";
    }
};

int main(int argc, char const *argv[])
{
    concrete_io cio;
    // Create new game
    std::cout << "Please enter your name:\n";
    std::string name;
    std::cin >> name;
    std::cout << "Please enter number of pegs:\n";
    int pegs;
    std::cin >> pegs;
    while (true)
    {

        run_game(cio, get_random_code());
        std::cout << "Would you like to play again? (y/n)\n";
        std::string answer;
        std::cin >> answer;
        if (answer == "n")
        {
            break;
        }
    }
    return 0;
}
