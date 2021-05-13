#include "Virologist.hpp"

using namespace std;
using namespace pandemic;

Player& Virologist::treat(City c){
    if(current_city != c){
        if(cards.count(c) == 0){
            throw invalid_argument{"You dont have the " + cities_names[c] + " card"};
        }
        cards.erase(c);
    }
    else if(game_board[c] == 0){
        throw invalid_argument{"There is no disease cubes in " + cities_names[c]};
    }
    else if(game_board.discoverd_cure[game_board.world_map[c].color]){
        game_board[c] = 0;
    }   
    game_board[c]--;
    return *this;
}