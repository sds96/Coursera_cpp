#ifndef BUSMANAGER_H_
#define BUSMANAGER_H_

#include "Bus_and_Stop.h"
#include "json.h"
#include <string>
#include <set>
#include <unordered_map>
#include <iomanip>

struct Bus_Response{
    std::string bus_name="";
    int stops_number = 0;
    int unique_stops_number = 0;
    double route_length = 0.0;
    double curv = 0.0;
    bool exist = true;
    int id = 0;
};

struct Stop_Response{
	std::string name="";
	std::set<std::string> buses;
    bool exist = true;
    int id = 0;
};

std::ostream& operator<<(std::ostream& os, const Bus_Response& response);
std::ostream& operator<<(std::ostream& os, const Stop_Response& response);


class BusManager{
	std::unordered_map<std::string, Bus> buses;
	std::unordered_map<std::string, BusStop> stops;
public:
	BusManager(){};

	void ReadStop(const Json::Node& node);

	void ReadBus(const Json::Node& node);

	void PrintAll(std::ostream& os = std::cout) const;

	Bus_Response Print_Bus(const Json::Node& node) const;

	Stop_Response Print_Stop(const Json::Node& node) const;

	void Update();
};

#endif /* BUSMANAGER_H_ */