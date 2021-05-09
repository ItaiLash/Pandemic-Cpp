#pragma once
#include "CityInfo.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>

using namespace std;

namespace pandemic {

    class Board {

        private:
            std::map<const City, CityInfo> world_map;

        public:
            Board(){
                init_world_map();
            }
            int& operator[](City c);
            bool is_clean();
            friend std::ostream& operator<<(std::ostream& out, const Board& b);

            void init_world_map();
    };
}