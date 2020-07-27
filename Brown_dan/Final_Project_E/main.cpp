#include "Geo.h"
//#include "test_runner.h"
#include "BusManager.h"
#include "Bus_and_Stop.h"
#include "json.h"

using namespace std;

void Read_DataBase(BusManager& bm, Json::Document& doc){
	const auto& settings = doc.GetRoot().AsMap().at("routing_settings").AsMap();
	bm.ReadSettings(settings);

	const auto& queries_array = doc.GetRoot().AsMap().at("base_requests").AsArray();
	for(auto& q: queries_array){
		if(q.AsMap().at("type").AsString() == "Stop"){
			bm.ReadStop(q);
		} else if (q.AsMap().at("type").AsString() == "Bus"){
			bm.ReadBus(q);
		}
	}
	bm.Update();
}

void Answer_DataBase(BusManager& bm, Json::Document& doc, ostream& os = cout){
	const auto& queries_array = doc.GetRoot().AsMap().at("stat_requests").AsArray();
	os << "[";
	int coma_count = queries_array.size()-1;
	for(const auto& q: queries_array){
		if(q.AsMap().at("type").AsString() == "Stop"){
			os << bm.Print_Stop(q);
		} else if (q.AsMap().at("type").AsString() == "Bus"){
			os << bm.Print_Bus(q);
		} else if (q.AsMap().at("type").AsString() == "Route"){
			os << bm.Print_Route(q);
		}
		if(coma_count>0) os << ", ";
		coma_count--;
	}
	os << "]";
}

int main() {
	//freopen("C:/Coursera/projects_eclipse/Brown_dan/Final_Project_E/Test4.txt", "r", stdin);
	BusManager bm;
	Json::Document doc = Json::Load(cin);
	Read_DataBase(bm, doc);
	//freopen("C:/Coursera/projects_eclipse/Brown_dan/Final_Project_E/Test4_my.txt", "w", stdout);
	Answer_DataBase(bm, doc, cout);
	return 0;
}
