#include <string_view>

namespace mastermind
{
    class game_io;
    void run_game(game_io& io_callback, std::string_view code);
}