/*
 * responses.h
 *
 *  Created on: 9 окт. 2019 г.
 *      Author: ƒмитрий
 */
#pragma once
#include <vector>
#include <string>

struct BusesForStopResponse { std::vector<std::string> buses_for_stop;};

struct StopsForBusResponse {  std::vector<std::string> stops_for_bus;};

struct AllBusesResponse {  std::vector<std::string> all_buses;};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
