#pragma once
#include "CityInfo.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>

using namespace std;

namespace pandemic {

    class Board {

        public:
            std::map<const City, CityInfo> world_map;
            std::map<Color, bool> discoverd_cure = {{Black, false}, {Blue, false}, {Red, false}, {Yellow, false}};
        public:
            Board(){
                init_world_map();
            }
            int& operator[](City c);
            bool is_clean();
            void cured(Color c);
            void remove_cures();
            friend std::ostream& operator<<(std::ostream& out, const Board& b);

            void init_world_map();
    };
}