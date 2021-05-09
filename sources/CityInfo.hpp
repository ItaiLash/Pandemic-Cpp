#pragma once
#include <map>
#include <set>
#include "City.hpp"
#include "Color.hpp"

namespace pandemic {

    class CityInfo {

    public:
        const City city;
        const std::string name;
        const std::set<City> neighber;
        int disease_cubes;
        bool stations;
        const Color color;

    public:

        CityInfo(const City c) : city(c), color(cities_colors[city]), name(cities_names[city]), disease_cubes(0),stations(false) {}
        ~CityInfo() {}

        std::set<City> get_neighbors(){
            return connections[city];
        }

        bool is_neighbor(City c){
            bool flag = false;
            for(City current : connections[c]){
                if(current == c){
                    flag = true;
                }
            }
            return flag;
        }

        City get_city(){
            return city;
        }

        int& get_disease_cubes(){
            return disease_cubes;
        }

        void increase_disease_cubes(){
            disease_cubes++;
        }

        void decrease_disease_cubes(){
            disease_cubes++;
        }

        Color get_color(){
            return color;
        }

        bool there_is_stations() const{
            return stations;
        }

        std::map<City, std::set<City>> connections {
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

    };

}