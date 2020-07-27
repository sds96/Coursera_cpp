#include "BusManager.h"

using namespace std;

ostream& operator<<(ostream& os, const Bus_Response& response) {
    os << "Bus " << response.bus_name << ": ";
    if (response.exist) {
        os << response.stops_number << " stops on route, ";
        os << response.unique_stops_number << " unique stops, ";
        os << fixed << setprecision(6) << response.route_length << " route length";
    } else {
        os << "not found";
    }
    return os;
}

ostream& operator<<(ostream& os, const Stop_Response& response) {
    os << "Stop " << response.name << ": ";
    if (response.exist) {
    	if(!response.buses.size())
    		os << "no ";
    	os << "buses";
        for (const string& bus: response.buses){
        	os << " " << bus;
        }
    } else {
        os << "not found";
    }
    return os;
}

void BusManager::ReadStop(std::istream& is){
	BusStop stop;
	stop.Read_Stop(is);
	stops[stop.GetName()] = stop;
}

void BusManager::ReadBus(std::istream& is){
	Bus bus;
	bus.Read_Route(is);
	buses[bus.GetNumber()] = bus;
}

void BusManager::PrintAll(std::ostream& os) const{
	for(const auto& el : buses){
		os << "Bus number #" << el.first << " has stops: ";
		el.second.PrintStops();
		os << "\n";
	}
	for(const auto& el : stops){
		os << el.second << endl;
	}
};

Bus_Response BusManager::Print_Bus(std::istream& is) const{
	Bus_Response resp;
	try{
		is.ignore(1);
		string numb ="";
		getline(is, numb);
		resp.bus_name = numb;

		const Bus& curr_bus = buses.at(numb);
		double lenght(0);
		for(size_t i = 0; i < curr_bus.route.size()-1; ++i){
			lenght += ComputeDistance(stops.at(curr_bus.route[i]).coord, stops.at(curr_bus.route[i+1]).coord);
		}
		lenght = curr_bus.isCircle ? lenght : lenght*2;
		resp.route_length = lenght;

		resp.stops_number = curr_bus.isCircle ? curr_bus.route.size() : 2*curr_bus.route.size()-1;

		set<string> unique (curr_bus.route.begin(), curr_bus.route.end());
		resp.unique_stops_number = unique.size();

		return resp;
	} catch (...){
		resp.exist = false;
		return resp;
	}
};

Stop_Response BusManager::Print_Stop(std::istream& is) const{
	Stop_Response resp;
	try{
		is.ignore(1);
		string name ="";
		getline(is, name);
		resp.name = name;

		resp.buses = stops.at(name).buses;

		return resp;
	} catch (...){
		resp.exist = false;
		return resp;
	}
};

void BusManager::Update(){
	for(auto& curr_bus : buses){
		for(auto& stop: curr_bus.second.route){	// ��� ������ ��������� ��������
			stops.at(stop).buses.insert(curr_bus.second.GetNumber());	// �������� ���������, ��� �� ��� ���� ���� �������
		}
	}
}
