#include "OperationsExpert.hpp"

using namespace std;
using namespace pandemic;


Player& OperationsExpert::build(){
    game_board.world_map[current_city].stations = true;
    return *this;
}