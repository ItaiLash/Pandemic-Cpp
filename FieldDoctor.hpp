#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic{

    class FieldDoctor: public Player {

        public:
            FieldDoctor(Board& b, City c): Player(b, c, "FieldDoctor") {}
            Player& treat(City c) override;
    };

}