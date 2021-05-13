#include "Researcher.hpp"

using namespace std;
using namespace pandemic;

const int FIVE_CARDS = 5;

Player& Researcher::discover_cure(Color c){
    if(count_cards(c) < FIVE_CARDS){
        throw std::invalid_argument{"You need 5 " + colors_as_string[c] + " cards but you have " + to_string(count_cards(c)) + " " + colors_as_string[c] + " cards"};
    }
    erase_cards(FIVE_CARDS, c);
    game_board.discoverd_cure[c] = true;
    return *this;
}