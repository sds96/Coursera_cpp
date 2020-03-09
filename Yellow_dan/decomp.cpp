#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

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

struct BusesForStopResponse { vector<string> buses_for_stop;};

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

struct StopsForBusResponse {  vector<string> stops_for_bus;};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (!r.stops_for_bus.empty()){
        for(const auto& el: r.stops_for_bus)
            os << el << endl;
    }
    else 
        os << "No bus" << endl;
  return os;
}

struct AllBusesResponse {  vector<string> all_buses;};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (!r.all_buses.empty()){
        for(const auto& el: r.all_buses)
            os << el << endl;
    }
    else 
        os << "No buses" << endl;
  return os;
}

class BusManager {
private:
map<string, vector<string>> m_buses, m_stops;

public:
  void AddBus(const string& bus, const vector<string>& stops) {
    for(const auto& stop: stops){
        m_buses[bus].push_back(stop);
        m_stops[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse BFSR;
    if (m_stops.count(stop) !=0)
        BFSR.buses_for_stop = m_stops.at(stop);
    return BFSR;
  }

  StopsForBusResponse GetStopsForBus(const string& my_bus) const {
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

  AllBusesResponse GetAllBuses() const {
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

};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
