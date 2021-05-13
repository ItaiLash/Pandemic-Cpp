#include "GeneSplicer.hpp"

using namespace std;
using namespace pandemic;

const int FIVE_CARDS = 5;

Player& GeneSplicer::discover_cure(Color c){
    if(!game_board.world_map[current_city].stations){
        throw invalid_argument{"There is no research station in " + cities_names[current_city]};
    }
    if(cards.size() < FIVE_CARDS){
        throw std::invalid_argument{"You need 5 cards but you have " + to_string(cards.size()) + " cards"};
    }
    erase_any_five_cards();
    game_board.discoverd_cure[c] = true;
    return *this;
}

void GeneSplicer::erase_any_five_cards(){
    int count = 1;
    for(auto iter = cards.begin(); iter != cards.end(); count++){
        if(count == FIVE_CARDS) { 
            break; 
        }
        iter = cards.erase(iter);
        ++iter;
    }
}