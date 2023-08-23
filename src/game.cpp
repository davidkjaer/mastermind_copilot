#include "game_io.h"
#include <vector>

namespace mastermind
{
    struct judge_result
    {
        int black;
        int white;
    };

    [[nodiscard]] judge_result judge(std::string_view code, std::string_view guess)
    {
        judge_result result{0, 0};
        
        for (int i = 0; i < code.size(); ++i)
        {
            if (code[i] == guess[i])
            {
                ++result.black;
            }
        }

        std::vector<bool> seen(code.size());
        for (int j = 0; j < guess.size(); ++j)
        {
            for (int i = 0; i < code.size(); ++i)
            {
                if (!seen[i] && code[i] == guess[j])
                {
                    seen[i] = true;
                    ++result.white;
                    break;
                }
            }
        }

        result.white -= result.black;
        return result;
    }

    void run_game(game_io& io_callback, std::string_view code)
    {
        while (true)
        {
            const std::string current_guess = io_callback.get_next_guess();
            if (current_guess.empty())
                return;

            const auto result = judge(code, current_guess);
            if (result.black == code.size())
            {
                io_callback.game_won();
                return;
            }
            
            io_callback.show_result(result.black, result.white);

        }
    }

}