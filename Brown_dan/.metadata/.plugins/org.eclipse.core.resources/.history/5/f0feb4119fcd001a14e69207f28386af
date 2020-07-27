#ifndef BUS_AND_STOP_H_
#define BUS_AND_STOP_H_

#include "Geo.h"
#include <string>
#include <vector>
#include <set>

class BusStop{
public:
	Point coord;
	std::string name;
	std::set<std::string> buses;
public:
	BusStop(){};

	std::string GetName() const;

	void Read_Stop(std::istream& is);

	friend std::ostream& operator<<(std::ostream& os, const BusStop& stop);
};


class Bus{
public:
	std::string bus_number;
	std::vector<std::string> route;
	bool isCircle;
public:
	Bus() : bus_number(""), isCircle(false)
	{
	};

	std::string GetNumber() const { return bus_number; }

	void PrintStops() const;

	void Read_Route(std::istream& is);

};

#endif /* BUS_AND_STOP_H_ */
