#include "Player.hpp"

using namespace std;
using namespace pandemic;

const int CARDS_TO_CURE = 5;

Player& Player::take_card(City c){
    cards.insert(c);
    return *this;
}

Player& Player::drive(City c){
    if(current_city == c){
        throw invalid_argument{"You already in " + cities_names[current_city]};
    }
    if(!game_board.world_map[current_city].is_neighbor(c)){
        throw invalid_argument{"Yoy can't drive to " + cities_names[c] + " because it is not connected to " + cities_names[current_city]};
    }
    current_city = c;
    return *this;
}

Player& Player::fly_direct(City c){
    if(current_city == c){
        throw invalid_argument{"You already in " + cities_names[current_city]};
    }
    if(cards.count(c) == 0){
        throw invalid_argument{"You're missing the " + cities_names[c] + " card"};
    }
    cards.erase(c);
    current_city = c;
    return *this;
}

Player& Player::fly_charter(City c){
    if(current_city == c){
        throw invalid_argument{"You already in " + cities_names[current_city]};
    }
    if(cards.count(current_city) == 0){
        throw invalid_argument{"You're missing the " + cities_names[c] + " card"};
    }
    cards.erase(current_city);
    current_city = c;
    return *this;
}


Player& Player::fly_shuttle(City c){
    if(current_city == c){
        throw invalid_argument{"You already in " + cities_names[current_city]};
    }
    if(!game_board.world_map[current_city].there_is_stations()){
        throw invalid_argument{"In order to shuttle fly there must be a research station in the current city"};
    }
    if(!game_board.world_map[c].there_is_stations()){
        throw invalid_argument{"In order to shuttle fly there must be a research station in tour destination city"};
    }
    current_city = c;
    return *this;
}

Player& Player::build(){
    if(cards.count(current_city) == 0){
        throw invalid_argument{"You don't have " + cities_names[current_city] + " card"};
    }
    game_board.world_map[current_city].stations = true;
    cards.erase(current_city);
    return *this;
}

Player& Player::discover_cure(Color c){
    if(!game_board.world_map[current_city].stations){
        throw invalid_argument{"There is no research station in " + cities_names[current_city] };
    }
    int num_of_cards_in_color = count_cards(c);
    if(num_of_cards_in_color < CARDS_TO_CURE){
        throw invalid_argument{"You have " + to_string(num_of_cards_in_color) + "/"+ colors_as_string[c] };
    }
    erase_cards(CARDS_TO_CURE, c);
    game_board.cured(c);
    return *this;
}

Player& Player::treat(City c){
    if (current_city != c) {
        throw invalid_argument{"You must be in " + cities_names[c] +" to treat the disease"};
    }
    if (game_board[c] == 0) {
        throw invalid_argument{"No more disease cubes in " + cities_names[c]};
    }
    if (game_board.discoverd_cure[game_board.world_map[c].color]) {
        game_board[c] = 0;
    }
    else {
        game_board[c]--;
    }
    return *this;
}

string Player::role(){
    return player_role;
}

int Player::count_cards(Color c){
    int count = 0;
    for(City city : cards){
        if(cities_colors[city] == c){
            count++;
        }
    }
    return count;
}

void Player::erase_cards(int n, Color c){
    int count = 1;
    for(auto iter = cards.begin(); iter != cards.end(); count++){
        if(count == n) { 
            break; 
        }
        if(cities_colors[*iter] == c) {
            iter = cards.erase(iter);
        }
        else {
            ++iter;
        }
    }
}