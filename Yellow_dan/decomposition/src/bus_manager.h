/*
 * bus_manager.h
 *
 *  Created on: 9 окт. 2019 г.
 *      Author: ƒмитрий
 */

#pragma once

#include <vector>
#include <map>
#include <string>

#include "responses.h"


class BusManager {
private:
std::map<std::string, std::vector<std::string>> m_buses, m_stops;

public:
  void AddBus(const std::string& bus, const std::vector<std::string>& stops);

  BusesForStopResponse GetBusesForStop(const std::string& stop) const;

  StopsForBusResponse GetStopsForBus(const std::string& my_bus) const;

  AllBusesResponse GetAllBuses() const;
};
