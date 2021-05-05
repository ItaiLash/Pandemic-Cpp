#include <iostream>
#include <vector>
#include "doctest.h"

#include "Board.hpp"
#include "City.hpp"
#include "CityInfo.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"

using namespace pandemic;
using namespace std;

const int NUM_TESTS = 20;
const int N = 5;

City generate_random_connected_city(City city);
City generate_random_city();
City generate_random_city(Color c);

//////////////////////////////////////////////
////////////////////Board/////////////////////
//////////////////////////////////////////////
TEST_CASE ("operator[]") {
    Board board;
    board[Milan]=2;
    CHECK(board[Milan]==2);
    board[Paris]=3;
    CHECK(board[Paris]==3);
}
TEST_CASE ("isClean") {
    Board board;
    OperationsExpert oex{board,Paris};
    board[Paris]=1;
    oex.take_card(Paris);
    CHECK(board.is_clean()==false);
    oex.treat(Paris);
    CHECK(board.is_clean()==true);
}

//////////////////////////////////////////////
////////////////////Player////////////////////
//////////////////////////////////////////////

//Dispatcher - When he is at a research station, 
//he can perform a "direct flight" operation to any city he wants, 
//without throwing a city card.
TEST_CASE("Dispatcher"){
    Board board;
    for(int i = 0 ; i < NUM_TESTS ; i++) {
        City current_city = generate_random_city();
        Dispatcher dispatcher{board, current_city};
        CHECK(dispatcher.role() == "Dispatcher");

        CHECK_NOTHROW(dispatcher.take_card(current_city));
        CHECK_NOTHROW(dispatcher.build());
        for(int j = 0 ; j < NUM_TESTS ; j++) {
            City next_city = generate_random_city();
            CHECK_NOTHROW(dispatcher.fly_direct(next_city));
            CHECK_NOTHROW(dispatcher.take_card(next_city));
            CHECK_NOTHROW(dispatcher.build());
        }
    }
}

//Field Doctor - Can perform a "treat" operation not only in the city he is in 
//but in any city near the city he is in (according to the context map), 
//without throwing a city card
TEST_CASE("FieldDoctor"){
    Board board;
    for(int i = 0; i < NUM_TESTS; i++) {
        City current_city = generate_random_city();
        FieldDoctor field_doctor{board, current_city};
        CHECK(field_doctor.role() == "FieldDoctor");

        for(int j = 0; j < 20; j++) {
            City near_city = generate_random_connected_city(current_city);
            board[near_city] = 5;
            CHECK(board[near_city] == 5);
            CHECK_NOTHROW(field_doctor.treat(near_city));
            CHECK(board[near_city] == 4);
            field_doctor.drive(near_city);
        }
    }
}

//Gene Splicer - Can perform a "discover cure" operation with the help
//of 5 cards, not necessarily from the color of the disease
TEST_CASE("GeneSplicer"){
    for(int i = 0; i < NUM_TESTS; i++) {
        Board board;
        City current_city = generate_random_city();
        GeneSplicer gene_splicer{board, current_city};
        CHECK(gene_splicer.role() == "GeneSplicer");

        CHECK_NOTHROW(gene_splicer.take_card(current_city).build());

        CityInfo current_city_info {current_city};
        Color color = current_city_info.get_color();

        for(int i = 0; i < 5; i++) {
            gene_splicer.take_card(generate_random_city());
        }
        CHECK_NOTHROW(gene_splicer.discover_cure(color));
    }
}

//Medic - When he performs a "treat" operation,
//he removes all the disease cubes from the city he is in, and not just one.
TEST_CASE("Medic"){
    for(int i = 0; i < NUM_TESTS; i++) {
        Board board;
        City current_city = generate_random_city();
        Medic medic{board, current_city};
        CHECK(medic.role() == "Medic");

        medic.take_card(current_city);
        for(int j = 0; j < NUM_TESTS; j++) {
            City next_city = generate_random_city();
            CHECK_NOTHROW(medic.take_card(next_city).fly_charter(next_city));
            board[next_city] = 5;
            CHECK(board[next_city] == 5);
            CHECK_NOTHROW(medic.treat(next_city));
            CHECK(board[next_city] == 0);
        }
    }
}

//Operations Expert - Can perform a "construction" operation in any city he is in,
//without throwing a suitable city card.
TEST_CASE("OperationsExpert"){
    Board board;
    for(int i = 0; i < NUM_TESTS; i++) {
        City current_city = generate_random_city();
        OperationsExpert operations_expert{board, current_city};
        CHECK(operations_expert.role() == "OperationsExpert");

        for(int j = 0; j < NUM_TESTS; j++) {
            City current = generate_random_connected_city(current);
            operations_expert.drive(current);
            CHECK_NOTHROW(operations_expert.build());
        }
    }
}

//Researcher - Can perform a "discover cure" operation in any city - does not 
//have to be at a research station.
TEST_CASE("Researcher"){
    for(int i = 0; i < NUM_TESTS; i++) {
        Board board;
        City current_city = generate_random_city();
        Researcher researcher{board, current_city};
        CHECK(researcher.role() == "Researcher");

        for(int j = 0; j < 20; j++) {
            City next_city = generate_random_city();
            CHECK_NOTHROW(researcher.take_card(next_city).fly_direct(next_city));
            CityInfo city_info{current_city};
            CHECK_FALSE(city_info.there_is_stations());
            Color current_color = city_info.get_color();

            for(int k=0 ; k<5 ; k++){
                City city = generate_random_city(current_color);
                CHECK_NOTHROW(researcher.take_card(city));
            }
            CHECK_NOTHROW(researcher.discover_cure(current_color));
        }
    }
}

//Scientist - Can perform a "cure discovery" operation with only n cards 
//(instead of 5), where the parameter n is passed in the constructor
TEST_CASE("Scientist"){
    for(int i = 0; i < N; i++) {
        Board board;
        City current_city = generate_random_city();
        Scientist scientist{board, current_city, i};
        CHECK(scientist.role() == "Scientist");

        for(int j = 0 ; j < NUM_TESTS ; j++) {
            City next_city = generate_random_city();
            CHECK_NOTHROW(scientist.take_card(next_city).fly_direct(next_city));
            CHECK_NOTHROW(scientist.take_card(next_city).build());

            CityInfo city_info{current_city};
            Color current_color = city_info.get_color();
            for(int k=0 ; k<=i ; k++){
                City city = generate_random_city(current_color);
                CHECK_NOTHROW(scientist.take_card(city));
            }
            CHECK_NOTHROW(scientist.discover_cure(current_color));
        }
    }
}

//Virologist - Can perform a "treat" operation, not only in the city it is in,
//but in any city in the world - by throwing a card of that city.
TEST_CASE("Virologist"){
    Board board;
    for(int i = 0; i < NUM_TESTS; i++) {
        City current_city = generate_random_city();
        Virologist virologist{board, current_city};
        CHECK(virologist.role() == "Virologist");

        for(int j = 0; j < NUM_TESTS; j++) {
         City next_city =  generate_random_city();
            if(next_city != current_city) {
                CHECK_THROWS(virologist.treat(next_city));
            }
            board[next_city] = 5;
            CHECK(board[next_city] == 5);
            CHECK_NOTHROW(virologist.take_card(next_city).treat(next_city));
            CHECK(board[next_city] == 4);
        }
    }
}


const std::map<City, vector<City>> connections {
    { Algiers, {Madrid, Paris, Istanbul, Cairo } },
    { Atlanta, {Chicago, Miami, Washington } },
    { Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi } },
    { Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong } },
    { Beijing, {Shanghai, Seoul } },
    { Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires } },
    { BuenosAires, {Bogota, SaoPaulo } },
    { Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh } },
    { Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta } },
    { Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal } },
    { Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata } },
    { Essen, {London, Paris, Milan, StPetersburg } },
    { HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila } },
    { HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei } },
    { Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow } },
    { Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney } },
    { Johannesburg, {Kinshasa, Khartoum } },
    { Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi } },
    { Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg } },
    { Kinshasa, {Lagos, Khartoum, Johannesburg } },
    { Kolkata, {Delhi, Chennai, Bangkok, HongKong } },
    { Lagos, {SaoPaulo, Khartoum, Kinshasa } },
    { Lima, {MexicoCity, Bogota, Santiago } },
    { London, {NewYork, Madrid, Essen, Paris } },
    { LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney } },
    { Madrid, {London, NewYork, Paris, SaoPaulo, Algiers } },
    { Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney } },
    { MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota } },
    { Miami, {Atlanta, MexicoCity, Washington, Bogota } },
    { Milan, {Essen, Paris, Istanbul } },
    { Montreal, {Chicago, Washington, NewYork } },
    { Moscow, {StPetersburg, Istanbul, Tehran } },
    { Mumbai, {Karachi, Delhi, Chennai } },
    { NewYork, {Montreal, Washington, London, Madrid } },
    { Osaka, {Taipei, Tokyo } },
    { Paris, {Algiers, Essen, Madrid, Milan, London } },
    { Riyadh, {Baghdad, Cairo, Karachi } },
    { SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila } },
    { Santiago, {Lima } },
    { SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid } },
    { Seoul, {Beijing, Shanghai, Tokyo } },
    { Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo } },
    { StPetersburg, {Essen, Istanbul, Moscow } },
    { Sydney, {Jakarta, Manila, LosAngeles } },
    { Taipei, {Shanghai, HongKong, Osaka, Manila } },
    { Tehran, {Baghdad, Moscow, Karachi, Delhi } },
    { Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco } },
    { Washington, {Atlanta, NewYork, Montreal, Miami } }
};

const vector<City> cities {
    Algiers, Atlanta, Baghdad, Bangkok, Beijing, Bogota, BuenosAires, Cairo, Chennai,
    Chicago, Delhi, Essen, HoChiMinhCity, HongKong, Istanbul, Jakarta, Johannesburg,
    Karachi, KePasio, Khartoum, Kinshasa, Kolkata, Lagos, Lima, London, LosAngeles,
    Madrid, Manila, MexicoCity, Miami, Milan, Montreal, Moscow, Mumbai, NewYork,
    Osaka, Paris, Riyadh, SanFrancisco, Santiago, SaoPaulo, Seoul, Shanghai, StPetersburg,
    Sydney, Taipei, Tehran, Tokyo, Washington
};

const std::map<Color, vector<City>> cities_by_colors {
    {Black, {Algiers, Baghdad, Cairo, Chennai, Delhi, Istanbul, Karachi, Kolkata, Moscow, Mumbai, Riyadh, Tehran}},
    {Blue, {Atlanta, Chicago, Essen, London, Madrid, Milan, Montreal, NewYork, Paris, SanFrancisco, StPetersburg, Washington}},
    {Red, {Bangkok, Beijing, HoChiMinhCity, HongKong, Jakarta, Manila, Osaka, Seoul, Shanghai, Sydney, Taipei, Tokyo}},
    {Yellow, {Bogota, BuenosAires, Johannesburg, Khartoum, Kinshasa, Lagos, Lima, LosAngeles, MexicoCity, Miami, Santiago, SaoPaulo}}
};

const vector<Color> colors {Black, Blue, Red, Yellow};

City generate_random_connected_city(City city){
    size_t idx = (size_t)rand() % (size_t)connections.at(city).size();
    return connections.at(city).at(idx);
}

City generate_random_city(){
    size_t idx = (size_t)rand() % 48;
    return cities.at(idx);
}

City generate_random_city(Color c){
    size_t idx = (size_t)rand() % 12;
    return cities_by_colors.at(c).at(idx);
}