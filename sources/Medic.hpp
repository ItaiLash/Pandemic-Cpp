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
            Player& drive(City c) override;
            Player& fly_direct(City c) override;
            Player& fly_charter(City c) override;
            Player& fly_shuttle(City c) override;
    };
    
}