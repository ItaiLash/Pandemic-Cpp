#include "Dispatcher.hpp"

using namespace std;
using namespace pandemic;

Player& Dispatcher::fly_direct(City c){
    if(current_city == c){
        throw invalid_argument{"You already in " + cities_names[current_city]};
    }
    if(game_board.world_map[current_city].stations) {
        current_city = c;
    }
    else {
        return Player::fly_direct(c);
    }
    return *this;
}