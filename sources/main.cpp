#include <iostream>
#include <string>
#include <map>
#include "Board.hpp"
#include "City.hpp"
#include "CityInfo.hpp"

#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace std;
using namespace pandemic;


Color get_color() {
    while(true) {
        cout << "Please choose a color:" << endl;
        cout << "(1)Black\n(2)Blue\n(3)Red\n(4)Yellow\n(9)EXIT\n" << endl;
        int color_id;
        cin >> color_id;
        if(color_id == 9) { exit(1); }
        if(color_id < 0 || color_id > 4) {
            cout << "Invalid input - please try again" << endl << endl;
        } else {
            return static_cast<Color>(color_id-1);
        }
    }
}

City get_city(bool first_city = false) {
    while(true) {
        if(first_city){
            cout << "Please choose your start city:" << endl;
        }
        else{
        cout << "Please choose a city:" << endl;
        }
        cout << "(1)Algiers (2)Atlanta (3)Baghdad (4)Bangkok (5)Beijing (6)Bogota (7)BuenosAires (8)Cairo (9)Chennai (10)Chicago\n" << 
                "(11)Delhi (12)Essen (13)HoChiMinhCity (14)HongKong (15)Istanbul (16)Jakarta (17)Johannesburg (18)Karachi (19)Khartoum (20)Kinshasa\n" <<
                "(21)Kolkata (22)Lagos (23)Lima (24)London (25)LosAngeles (26)Madrid (27)Manila (28)MexicoCity (29)Miami (30)Milan\n" << 
                "(31)Montreal (32)Moscow (33)Mumbai (34)NewYork (35)Osaka (36)Paris (37)Riyadh (38)SanFrancisco (39)Santiago (40)SaoPaulo\n" <<
                "(41)Seoul (42)Shanghai (43)StPetersburg (44)Sydney (45)Taipei (46)Tehran (47)Tokyo (48)Washington\n" <<
                "(99)EXIT" << endl << endl;
        int city_id;
        cin >> city_id;
        if(city_id == 99) { exit(1); }
        if(city_id < 1 || city_id > 48) {
            cout << "Invalid input - please try again" << endl << endl;
        } else {
            return static_cast<City>(city_id-1);
        }
    }
}

int get_player_role() {
    while(true) {
        cout << "Please choose your player role:" << endl;
        cout << "(1)Player (2)Dispatcher (3)FieldDoctor (4)GeneSplicer (5)Medic (6)OperationsExpert (7)Researcher (8)Scientist (9)Virologist (99)EXIT" << endl << endl;
        int role_id;
        cin >> role_id;
        if(role_id == 99) { exit(1); }
        if(role_id < 1 || role_id > 9) {
            cout << "Invalid input - please try again" << endl << endl;
        } else {
            return role_id;
        }
    }
}

int get_n() {
    while(true) {
        cout << "Please enter the cards limit for scientist:" << endl;
        int n;
        cin >> n;
        if(n < 0) {
            cout << "Invalid input - please try again" << endl;
        } else {
            return n;
        }
    }
}

int main() {
    Board board;
    City start_city = get_city(true);
    int role_id = get_player_role();
    int n = 5;
    if(role_id == 8){
        n = get_n();
    }

    map<int,Player*> players = {{1,new Player{board, start_city}}, {2, new Dispatcher(board, start_city)}, {3,new FieldDoctor{board, start_city}}, {4,new GeneSplicer{board, start_city}},
                                {5, new Medic{board, start_city}}, {6,new OperationsExpert{board, start_city}}, {7,new Researcher{board, start_city}}, {8,new Scientist{board, start_city,n}}, {9,new Virologist{board, start_city}}};


    while(true) {
        cout << "Select the action you want to preform:" << endl;
        cout << "Player Operations:\n(1)drive (2)fly direct (3)fly charter (4)fly shuttle (5)build\n"<< 
                "(6)discover_cure (7)treat (8)take card (9)role" << endl << endl;
        cout << "Board Operations:\n(10)Print Board (11)is clean (12)remove cures " << endl << endl;
        cout << "More Operations:\n(13)current city (14)connections of current city (15)set deases cubes (16)my cards" << endl << endl;
        int operation;
        cin >> operation;
        City city = start_city;
        CityInfo city_info{city};
        set<City> connection = city_info.get_neighbors();
        Color color;
        if(operation == 0) { exit(1); }
        if(operation < 0 || operation > 16) {
            cout << "Invalid operation - please try again" << endl << endl;
        } else {
            switch (operation) {
                case 1:
                    cout << "Choose city to drive to:" << endl;
                    city = get_city();
                    try{
                        (*(players[role_id])).drive(city);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player drive to " << cities_names[city] << endl << endl;
                    break;
                case 2:
                    cout << "Choose city to fly to:" << endl;
                    city = get_city();
                    try{
                        (*(players[role_id])).fly_direct(city);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player fly to " << cities_names[city] << endl << endl;
                    break;
                case 3:
                    cout << "Choose city to fly to:" << endl;
                    city = get_city();
                    try{
                        (*(players[role_id])).fly_charter(city);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player fly to " << cities_names[city] << endl << endl;
                    break;
                case 4:
                    cout << "Choose city to fly to:" << endl;
                    city = get_city();
                    try{
                        (*(players[role_id])).fly_shuttle(city);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player fly to " << cities_names[city] << endl << endl;
                    break;
                case 5:
                    try{
                        (*(players[role_id])).build();
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player build station" << endl << endl;
                    break;
                case 6:
                    cout << "Choose color:" << endl;
                    color = get_color();
                    try{
                        (*(players[role_id])).discover_cure(color);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player discover cure" << endl << endl;
                    break;
                case 7:
                    cout << "Choose city to treat:" << endl;
                    city = get_city();
                    try{
                        (*(players[role_id])).treat(city);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player treat " << cities_names[city] << endl << endl;
                    break;
                case 8:
                    cout << "Choose city to take its card:" << endl;
                    city = get_city();
                    try{
                        (*(players[role_id])).take_card(city);
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Player taken card " << cities_names[city] << endl << endl;
                    break;
                case 9:
                    cout << "Player role is: " << (*(players[role_id])).role() << endl << endl;
                    break;
                case 10:
                    cout << board << endl << endl;
                    break;
                case 11:
                    cout << "The board is clean: " << board.is_clean() << endl << endl;
                    break;
                case 12:
                    try{
                        board.remove_cures();
                    }
                    catch(const std::exception& e){
                        cout<<e.what()<<endl;
                        break;
                    }
                    cout << "Board removed cures" << endl << endl;
                    break;
                case 13:
                    cout << "Current city: " << cities_names[get_city()]<< endl << endl;
                    break;
                case 14:
                    cout << "Connections: [ ";
                    for(const auto& c : connection) {
                        cout << cities_names[c] << ' ';
                    }
                    cout << ']' << endl << endl;
                    break;
                case 15:
                    cout << "Please choose a city:" << endl;
                    cout << "(1)Algiers (2)Atlanta (3)Baghdad (4)Bangkok (5)Beijing (6)Bogota (7)BuenosAires (8)Cairo (9)Chennai (10)Chicago\n" << 
                            "(11)Delhi (12)Essen (13)HoChiMinhCity (14)HongKong (15)Istanbul (16)Jakarta (17)Johannesburg (18)Karachi (19)Khartoum (20)Kinshasa\n" <<
                            "(21)Kolkata (22)Lagos (23)Lima (24)London (25)LosAngeles (26)Madrid (27)Manila (28)MexicoCity (29)Miami (30)Milan\n" << 
                            "(31)Montreal (32)Moscow (33)Mumbai (34)NewYork (35)Osaka (36)Paris (37)Riyadh (38)SanFrancisco (39)Santiago (40)SaoPaulo\n" <<
                            "(41)Seoul (42)Shanghai (43)StPetersburg (44)Sydney (45)Taipei (46)Tehran (47)Tokyo (48)Washington\n" <<
                            "(99)EXIT" << endl << endl;
                    int city_id;
                    cin >> city_id;
                    cout << "how many deases cubes would you like to set to this city?" << endl;
                    int cubes;
                    cin >> cubes;
                    board[static_cast<City>(city_id-1)]=cubes;
                    break;
                case 16: 
                    set<City> my_cards = (*(players[role_id])).get_cards();
                    cout << "Cards: [ ";
                    for(const auto& c : my_cards) {
                        cout << cities_names[c] << ' ';
                    }
                    cout << ']' << endl << endl;
                    break;
            }
        }
    }

    exit(1);
}