#include "Bus_and_Stop.h"

using namespace std;

//================== BusStop ===============

std::string BusStop::GetName() const{
		return name;
	}

void BusStop::Read_Stop(const Json::Node& node) {
	const auto& map = node.AsMap();
	name = map.at("name").AsString();
    double longitude, latitude;
    try {
        longitude = map.at("longitude").AsDouble();
    } catch(...) {
        longitude = map.at("longitude").AsInt();
    }

    try {
        latitude = map.at("latitude").AsDouble();
    } catch(...) {
        latitude = map.at("latitude").AsInt();
    }

	coord.SetLatitude(latitude);
	coord.SetLongitude(longitude);
	for(const auto& el: map.at("road_distances").AsMap()){
		real_distance[el.first] = el.second.AsInt();
	}
}

std::ostream& operator<<(std::ostream& os, const BusStop& stop){
	os << "Bus_Stop:" << '"' << stop.name <<'"' << ". Coordinates: " << stop.coord;
	return os;
};

//================== Bus ===================

void Bus::PrintStops() const {
	for(const auto& stop: route){
		cout << stop << " ";
	}
}

void Bus::Read_Route(const Json::Node& node){
	const auto& map = node.AsMap();
	bus_number = map.at("name").AsString();
	isCircle = map.at("is_roundtrip").AsBool();
	for (const auto& el : map.at("stops").AsArray()){
		route.push_back(el.AsString());
	}
};
