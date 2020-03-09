/*
 * query.cpp
 *
 *  Created on: 9 окт. 2019 г.
 *      Author: ƒмитрий
 */

#include "query.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

istream& operator >> (istream& is, Query& q) {
	string typeStr;
	is >> typeStr;
	if (typeStr == "NEW_BUS")
	{
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count = 0;
		is >> stop_count;
		q.stops.clear();
		for (auto i = 0; i < stop_count; ++i)
		{
			string stop;
			is >> stop;
			q.stops.push_back(stop);
		}
	}
	else if (typeStr == "BUSES_FOR_STOP")
	{
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (typeStr == "STOPS_FOR_BUS")
	{
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (typeStr == "ALL_BUSES")
		q.type = QueryType::AllBuses;
  return is;
}



