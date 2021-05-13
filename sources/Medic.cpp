#include "Medic.hpp"

using namespace std;
using namespace pandemic;

Player& Medic::treat(City c) {
    if (current_city != c) {
        throw invalid_argument{"You must be in " + cities_names[c] +" to treat the disease"};
    }
    if (game_board[c] == 0) {
        throw invalid_argument{"There is no disease cubes in " + cities_names[c]};
    }
    game_board[c] = 0;
    return *this;
}

Player& Medic::drive(City c){
    Player::drive(c);
    if (game_board.discoverd_cure[game_board.world_map[c].color]) {
        game_board[c] = 0;
    }
    return *this;
}

Player& Medic::fly_direct(City c){
    Player::fly_direct(c);
    if (game_board.discoverd_cure[game_board.world_map[c].color]) {
        game_board[c] = 0;
    }
    return *this;
}

Player& Medic::fly_charter(City c){
    Player::fly_charter(c);
    if (game_board.discoverd_cure[game_board.world_map[c].color]) {
        game_board[c] = 0;
    }
    return *this;
}

Player& Medic::fly_shuttle(City c){
    Player::fly_shuttle(c);
    if (game_board.discoverd_cure[game_board.world_map[c].color]) {
        game_board[c] = 0;
    }
    return *this;
}
