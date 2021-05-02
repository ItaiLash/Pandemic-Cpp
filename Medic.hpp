#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic{

    class Medic: public Player {

        public:
            Medic(Board& b, City c): Player(b, c, "Medic") {}
            Player& treat(City c) override;
    };
    
}