#pragma once
#include "Board.hpp"
#include "CityInfo.hpp"
#include <set>
using namespace std;

namespace pandemic {

    class Player {

        protected:
            Board& game_board;
            set<City> cards;
            City current_city;
            string player_role;

        public:
            Player(Board& b, City c, string r = "Player"): game_board(b), current_city(c), player_role(r) {}
            virtual Player& drive(City c);
            virtual Player& fly_direct(City c);
            virtual Player& fly_charter(City c);
            virtual Player& fly_shuttle(City c);
            virtual Player& build();
            virtual Player& discover_cure(Color c);
            virtual Player& treat(City c);
            Player& take_card(City c);
            string role();

        protected:
            int count_cards(Color c);
            void erase_cards(int n, Color c);
    };

}