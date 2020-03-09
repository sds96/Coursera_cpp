/*
 * responses.cpp
 *
 *  Created on: 9 окт. 2019 г.
 *      Author: ƒмитрий
 */

#include <iostream>
#include <vector>
#include <string>

#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (!r.buses_for_stop.empty()){
        for(const auto& el: r.buses_for_stop)
            os << el << " ";
        os << endl;
    }
    else
        os << "No stop" << endl;
  return os;
}



ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (!r.stops_for_bus.empty()){
        for(const auto& el: r.stops_for_bus)
            os << el << endl;
    }
    else
        os << "No bus" << endl;
  return os;
}


ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (!r.all_buses.empty()){
        for(const auto& el: r.all_buses)
            os << el << endl;
    }
    else
        os << "No buses" << endl;
  return os;
}




