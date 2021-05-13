#include "Board.hpp"

using namespace std;
using namespace pandemic;

void Board::init_world_map(){
    world_map = {
        {City::Algiers,       CityInfo{City::Algiers}},
        {City::Atlanta,       CityInfo{City::Atlanta}},
        {City::Baghdad,       CityInfo{City::Baghdad}},
        {City::Bangkok,       CityInfo{City::Bangkok}},
        {City::Beijing,       CityInfo{City::Beijing}},
        {City::Bogota,        CityInfo{City::Bogota}},
        {City::BuenosAires,   CityInfo{City::BuenosAires}},
        {City::Cairo,         CityInfo{City::Cairo}},
        {City::Chennai,       CityInfo{City::Chennai}},
        {City::Chicago,       CityInfo{City::Chicago}},
        {City::Delhi,         CityInfo{City::Delhi}},
        {City::Essen,         CityInfo{City::Essen}},
        {City::HoChiMinhCity, CityInfo{City::HoChiMinhCity}},
        {City::HongKong,      CityInfo{City::HongKong}},
        {City::Istanbul,      CityInfo{City::Istanbul}},
        {City::Jakarta,       CityInfo{City::Jakarta}},
        {City::Johannesburg,  CityInfo{City::Johannesburg}},
        {City::Karachi,       CityInfo{City::Karachi}},
        {City::Khartoum,      CityInfo{City::Khartoum}},
        {City::Kinshasa,      CityInfo{City::Kinshasa}},
        {City::Kolkata,       CityInfo{City::Kolkata}},
        {City::Lagos,         CityInfo{City::Lagos}},
        {City::Lima,          CityInfo{City::Lima}},
        {City::London,        CityInfo{City::London}},
        {City::LosAngeles,    CityInfo{City::LosAngeles}},
        {City::Madrid,        CityInfo{City::Madrid}},
        {City::Manila,        CityInfo{City::Manila}},
        {City::MexicoCity,    CityInfo{City::MexicoCity}},
        {City::Miami,         CityInfo{City::Miami}},
        {City::Milan,         CityInfo{City::Milan}},
        {City::Montreal,      CityInfo{City::Montreal}},
        {City::Moscow,        CityInfo{City::Moscow}},
        {City::Mumbai,        CityInfo{City::Mumbai}},
        {City::NewYork,       CityInfo{City::NewYork}},
        {City::Osaka,         CityInfo{City::Osaka}},
        {City::Paris,         CityInfo{City::Paris}},
        {City::Riyadh,        CityInfo{City::Riyadh,}},
        {City::SanFrancisco,  CityInfo{City::SanFrancisco}},
        {City::Santiago,      CityInfo{City::Santiago}},
        {City::SaoPaulo,      CityInfo{City::SaoPaulo}},
        {City::Seoul,         CityInfo{City::Seoul}},
        {City::Shanghai,      CityInfo{City::Shanghai}},
        {City::StPetersburg,  CityInfo{City::StPetersburg}},
        {City::Sydney,        CityInfo{City::Sydney}},
        {City::Taipei,        CityInfo{City::Taipei}},
        {City::Tehran,        CityInfo{City::Tehran}},
        {City::Tokyo,         CityInfo{City::Tokyo}},
        {City::Washington,    CityInfo{City::Washington}}
    };
}

int& Board::operator[](City c) {
    return Board::world_map[c].disease_cubes;
}

bool Board::is_clean() {
    for (auto& kv : world_map) {
        if(kv.second.get_disease_cubes() > 0) {
            return false;
        }
    }
    return true;
}

void Board::remove_cures() {
    for (auto& kv : discoverd_cure) {
        kv.second = false;
    }
}


void Board::cured(Color c){
    discoverd_cure[c] = true;
}


std::ostream& pandemic::operator<<(std::ostream& out, const Board& b) {
    out << "-------------------------------------------------" << endl;
    out << "Disease level:" << endl;
    for(const auto& kv: b.world_map) {
        out << "\t" << cities_names[kv.first] << ": \t\t" << kv.second.disease_cubes << endl;
    }
    out << "Cure discovered:" << endl;
    for(const auto& kv: b.discoverd_cure) {
        if(kv.second){
            out << "\t" << colors_as_string[kv.first] << endl;
        }
    }
    out << "Research stations:" << endl;
    for(const auto& kv: b.world_map) {
        if(kv.second.there_is_stations()){
            out << "\t" << cities_names[kv.first] << endl;
        }
    }
    out << "-------------------------------------------------" << endl;
    return out;
}
