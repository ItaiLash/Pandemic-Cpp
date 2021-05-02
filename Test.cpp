#include <iostream>
#include "doctest.h"
#include "Board.hpp"
#include "CityInfo.hpp"
#include "OperationsExpert.hpp"
#include "FieldDoctor.hpp"
#include "Dispatcher.hpp"
#include "Scientist.hpp"
#include "Researcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "GeneSplicer.hpp"

using namespace pandemic;
using namespace std;

City random_city();

TEST_CASE ("test") {
    for(int i=0 ; i<30 ; i++){
        CHECK_EQ(1,1);
    }
}

TEST_CASE ("test") {
    CityInfo c(Algiers);
    std::set<City> cities = c.get_neighbors();
    CHECK_EQ(c.get_neighbors() , std::set<City>({City::Madrid, City::Paris, City::Istanbul, City::Cairo }));
}