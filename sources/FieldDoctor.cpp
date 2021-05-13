#include "FieldDoctor.hpp"

using namespace std;
using namespace pandemic;

Player& FieldDoctor::treat(City c){
    if (current_city != c && !game_board.world_map[current_city].is_neighbor(c)) {
        throw invalid_argument{cities_names[current_city] + " is not connected to " + cities_names[c]};
    }
    if (game_board[c] == 0) {
        throw invalid_argument{"There is no disease cubes in " + cities_names[c]};
    }
    if (game_board.discoverd_cure[game_board.world_map[c].color]) {
        game_board[c] = 0;
    }
    else {
        game_board[c]--;
    }
    return *this;
}