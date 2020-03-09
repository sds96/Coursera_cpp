/*
 * bus_manager.cpp
 *
 *  Created on: 9 окт. 2019 г.
 *      Author: ƒмитрий
 */

#include <map>
#include <vector>
#include <iostream>

#include "responses.h"
#include "bus_manager.h"

using namespace std;
  void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    for(const auto& stop: stops){
        m_buses[bus].push_back(stop);
        m_stops[stop].push_back(bus);
    }
  }

  BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse BFSR;
    if (m_stops.count(stop) !=0)
        BFSR.buses_for_stop = m_stops.at(stop);
    return BFSR;
  }

  StopsForBusResponse BusManager::GetStopsForBus(const string& my_bus) const {
    StopsForBusResponse SFBR;
    if(m_buses.count(my_bus) !=0){
        for (const auto& stop: m_buses.at(my_bus)){
            string tmp;
            tmp = "Stop " + stop +": ";
            if(m_stops.at(stop).size() == 1)
                tmp += "no interchange";
            else
                for(const auto& bus: m_stops.at(stop)){
                    if (bus != my_bus)
                        tmp = tmp + bus + " ";
                }
            SFBR.stops_for_bus.push_back(tmp);
        };
    }
    return SFBR;
  }

  AllBusesResponse BusManager::GetAllBuses() const {
      AllBusesResponse ABR;
      if (!m_buses.empty()){
          for(const auto& bus_item: m_buses){
              string tmp;
              tmp = "Bus " + bus_item.first + ": ";
              for( const auto& stop: bus_item.second){
                  tmp+= stop + " ";
              }
              ABR.all_buses.push_back(tmp);
          }
      }
      return ABR;
    }


