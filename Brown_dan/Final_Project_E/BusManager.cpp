#include "BusManager.h"
#include <cstdint>


using namespace std;

ostream& operator<<(ostream& os, const Bus_Response& response) {
    os << "{";
	os << '"' << "request_id" << '"' << ": " << response.id << ", ";
	if (response.exist) {
        os << fixed << setprecision(6) << '"' << "route_length" << '"' << ": " << response.route_length << ", ";
        os << '"' << "curvature" << '"' << ": " << response.curv << ", ";
        os << '"' << "stop_count" << '"' << ": " << response.stops_number << ", ";
        os << '"' << "unique_stop_count" << '"' << ": " << response.unique_stops_number;
    } else {
    	os << '"' << "error_message" << '"' << ": " << '"' << "not found" << '"';
    }
	os << "}";
    return os;
}

ostream& operator<<(ostream& os, const Stop_Response& response) {
    os << "{";
	os << '"' << "request_id" << '"' << ": " << response.id << ", ";
    if (response.exist) {
    	os << '"' << "buses" << '"' << ": ";
    	if(!response.buses.size())
    		os << "[]";
    	else{
    		os << "[";
    		int coma_count = response.buses.size()-1;
			for (const string& bus: response.buses){
				os << '"' << bus << '"';
				if(coma_count>0) os << ", ";
				coma_count--;
			}
			os << "]";
    	}
    } else {
    	os << '"' << "error_message" << '"' << ": " << '"' << "not found" << '"';
    }
	os << "}";
    return os;
}

ostream& operator<<(ostream& os, const Route_Response& response) {
	os << "{";
	os << '"' << "request_id" << '"' << ": " << response.id << ", ";
	if (response.exist) {
		os << '"' << "total_time" << '"' << ": " << response.total_time << ", ";
		os << '"' << "items" << '"' << ": [";
		int coma_count = response.items.size()-1;
		for (auto& item : response.items){
			os << "{";
			os << '"' << "type" << '"' << ": ";
			if(item.type == ItemType::BUS){
				os << '"' << "Bus" << '"' << ", ";
			}
			if(item.type == ItemType::WAIT){
				os << '"' << "Wait" << '"' << ", ";
			}

			os << '"' << "time" << '"' << ": " << item.time << ", ";

			if(item.type == ItemType::BUS){
				os << '"' << "bus" << '"' << ": " << '"' << item.bus << '"' << ", ";
				os << '"' << "span_count" << '"' << ": " << item.span_count;
			}
			if(item.type == ItemType::WAIT){
				os << '"' << "stop_name" << '"' << ": " << '"' << item.stop_name << '"';
			}

			os << "}";
			if(coma_count>0) os << ", ";
			coma_count--;
		}
		os << "]";
	} else {
		os << '"' << "error_message" << '"' << ": " << '"' << "not found" << '"';
	}
	os << "}";
	return os;
}

void BusManager::ReadStop(const Json::Node& node){
	BusStop stop;
	stop.Read_Stop(node);
	stops[stop.GetName()] = stop;
	stops_to_indexes[stop.GetName()] = stops.size()-1;
	indexes_to_stops[stops.size()-1] = stop.GetName();
}

void BusManager::ReadBus(const Json::Node& node){
	Bus bus;
	bus.Read_Route(node);
	buses[bus.GetNumber()] = bus;
}

void BusManager::ReadSettings(const Json::Node& settings){
	try{
		this->bus_velocity = settings.AsMap().at("bus_velocity").AsInt() * 1000.0 / 60.0;
	} catch (...){
		this->bus_velocity = settings.AsMap().at("bus_velocity").AsDouble() * 1000.0 / 60.0;
	}
	this->bus_wait_time = settings.AsMap().at("bus_wait_time").AsInt();
}

Bus_Response BusManager::Print_Bus(const Json::Node& node) const{
	Bus_Response resp;
	try{
		const auto& map = node.AsMap();
		string name = map.at("name").AsString();
		resp.bus_name = name;
		resp.id = map.at("id").AsInt();

		const Bus& curr_bus = buses.at(name);
		double calc_lenght(0);
		double true_lenght_f(0), true_lenght_b(0);
		for(size_t i = 0; i < curr_bus.route.size()-1; ++i){
			auto it = stops.at(curr_bus.route[i]).real_distance.find(curr_bus.route[i+1]);
			true_lenght_f += it->second;
			it = stops.at(curr_bus.route[i+1]).real_distance.find(curr_bus.route[i]);
			true_lenght_b += it->second;
			calc_lenght += ComputeDistance(stops.at(curr_bus.route[i]).coord, stops.at(curr_bus.route[i+1]).coord);
		}
		calc_lenght = curr_bus.isCircle ? calc_lenght : calc_lenght*2;

		resp.route_length = curr_bus.isCircle ? true_lenght_f : true_lenght_f + true_lenght_b;
		resp.curv = curr_bus.isCircle ? true_lenght_f/calc_lenght : (true_lenght_f + true_lenght_b)/calc_lenght;
		resp.stops_number = curr_bus.isCircle ? curr_bus.route.size() : 2*curr_bus.route.size()-1;

		set<string> unique (curr_bus.route.begin(), curr_bus.route.end());
		resp.unique_stops_number = unique.size();

		return resp;
	} catch (...){
		resp.exist = false;
		return resp;
	}
};

Stop_Response BusManager::Print_Stop(const Json::Node& node) const{
	Stop_Response resp;
	try{
		const auto& map = node.AsMap();
		string name = map.at("name").AsString();
		resp.name = name;
		resp.id = map.at("id").AsInt();

		resp.buses = stops.at(name).buses;

		return resp;
	} catch (...){
		resp.exist = false;
		return resp;
	}
};

Route_Response BusManager::Print_Route(const Json::Node& node) const{
	Route_Response resp;
	try{
		resp.id = node.AsMap().at("id").AsInt();
		size_t from = stops_to_indexes.at(node.AsMap().at("from").AsString());
		size_t to = stops_to_indexes.at(node.AsMap().at("to").AsString());
		if(from == to)
			return resp;
		const auto route_info = router->BuildRoute(from,to);
		for (size_t i = 0; i < route_info->edge_count; ++i){
			const auto edge_id = router->GetRouteEdge(route_info->id, i);
			const auto edge = graph->GetEdge(edge_id);
			// ���������
			resp.items.push_back(Item{ItemType::WAIT, static_cast<double>(bus_wait_time), indexes_to_stops.at(edge.from)," ",0});
			// ��������
			resp.items.push_back(Item{ItemType::BUS, edge.weight - static_cast<double>(bus_wait_time), "", edge_ind_to_info.at(edge_id).bus_name, edge_ind_to_info.at(edge_id).span_count});
		}

		resp.total_time = route_info->weight;
		return resp;
	} catch (std::exception& e){
		cerr << e.what();
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

	for(auto& stop : stops){
		for(auto& stop2 : stop.second.real_distance){
			auto it = stops.at(stop2.first).real_distance.find(stop.first);
			if(it == stops.at(stop2.first).real_distance.end())
				stops.at(stop2.first).real_distance[stop.first] = stop.second.real_distance[stop2.first];
		}
	}

	graph = new Graph::DirectedWeightedGraph<double>(stops.size());

	for(auto& curr_bus : buses){
		size_t r_size = curr_bus.second.route.size();
		for(size_t i = 0; i< r_size-1; ++i){
			size_t from = stops_to_indexes.at(curr_bus.second.route[i]);
			double distance(0.0);
			for(size_t j = i+1; j < r_size; ++j){
				size_t to = stops_to_indexes.at(curr_bus.second.route[j]);
				distance += stops[curr_bus.second.route[j-1]].real_distance[curr_bus.second.route[j]];
				size_t id = graph->AddEdge({from, to, distance/bus_velocity + static_cast<double>(bus_wait_time)});
				edge_ind_to_info[id] = {curr_bus.first, j-i};
			}
		}

		if(!curr_bus.second.isCircle){	// ������ �������� ������� ��� ������ ������
			for(int i = r_size-1; i > 0; i--){
				size_t from = stops_to_indexes.at(curr_bus.second.route[i]);
				double distance(0.0);
				for(int j = i-1; j >= 0; j--){
					size_t to = stops_to_indexes.at(curr_bus.second.route[j]);
					distance += stops[curr_bus.second.route[j+1]].real_distance[curr_bus.second.route[j]];
					size_t id = graph->AddEdge({from, to, distance/bus_velocity + static_cast<double>(bus_wait_time)});
					edge_ind_to_info[id] = {curr_bus.first, static_cast<size_t>(i-j)};
				}
			}
		}
		// �����
		/*for(size_t i = 0; i< r_size-1; ++i){
			size_t from = stops_to_indexes.at(curr_bus.second.route[i]);
			double distance(0.0);
			for(size_t j = i+1; j < r_size; ++j){
				distance += stops[curr_bus.second.route[j-1]].real_distance[curr_bus.second.route[j]];
			}
			for(size_t j = 0; j < r_size - 1; ++j){
				size_t to = stops_to_indexes.at(curr_bus.second.route[r_size-j-1]);
				distance += stops[curr_bus.second.route[r_size-1]].real_distance[curr_bus.second.route[r_size-j-1]];
				size_t id = graph->AddEdge({from, to, distance/bus_velocity + static_cast<double>(bus_wait_time)});
				edge_ind_to_info[id] = {curr_bus.first, r_size+j};
			}
		}*/

		if(curr_bus.second.isCircle){
			graph->AddEdge({stops_to_indexes[*curr_bus.second.route.begin()], stops_to_indexes[*(curr_bus.second.route.end()-1)], static_cast<double>(bus_wait_time)});
		}
	}

	router = new Graph::Router<double>(*graph);
}
