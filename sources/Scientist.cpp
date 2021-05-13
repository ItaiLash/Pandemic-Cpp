#include "Scientist.hpp"

using namespace std;
using namespace pandemic;

Player& Scientist::discover_cure(Color c) {
    if(!game_board.world_map[current_city].stations){
        throw invalid_argument{"There is no research station in " + cities_names[current_city]};
    }
    if(count_cards(c) < n){
        throw std::invalid_argument{"You need " + to_string(n) + " " + colors_as_string[c] + " cards but you have " + to_string(count_cards(c)) + " " + colors_as_string[c] + " cards"};
    }
    erase_cards(n, c);
    game_board.discoverd_cure[c] = true;
    return *this;
}