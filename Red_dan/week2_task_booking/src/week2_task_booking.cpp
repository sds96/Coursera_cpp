#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct event{
	string hotel_name;
	long long time;
	int client_id;
	int room_count;
};

struct thotel {
	int rooms_booked;
	int clients_count;
	map<int, int> client_to_count;
	thotel(){
		rooms_booked = 0;
		clients_count=0;
	}
};

class Booking_manager{
private:
	map<string, thotel> hotels;
	queue<event> events;
public:
	void book(long long time, string hotel_name, int client_id, int room_count){
		events.push({hotel_name, time,client_id,room_count});
		if (hotels[hotel_name].client_to_count.count(client_id) == 0)
		        {
		            ++hotels[hotel_name].clients_count;
		            hotels[hotel_name].client_to_count[client_id] = 0;
		        }
		        ++hotels[hotel_name].client_to_count[client_id];
		hotels[hotel_name].rooms_booked+=room_count;

		while(!events.empty() && (time - events.front().time >= 86400)){
			hotels[events.front().hotel_name].rooms_booked-=events.front().room_count;
			--hotels[events.front().hotel_name].client_to_count[events.front().client_id];
			            if (hotels[events.front().hotel_name].client_to_count[events.front().client_id] == 0)
			            {
			                --hotels[events.front().hotel_name].clients_count;
			                hotels[events.front().hotel_name].client_to_count.erase(events.front().client_id);
			            }
			events.pop();
		}
	};

	int clients_last_hour(string hotel_name){
		if (hotels.count(hotel_name) == 0)
			return 0;
		return hotels[hotel_name].clients_count;
	}

	int rooms_last_hour(string hotel_name){
		if (hotels.count(hotel_name) == 0)
			return 0;
		return hotels[hotel_name].rooms_booked;
	}
};

int main() {
	Booking_manager bm;
	int Q;
	cin>> Q;
	for(int i=0;i<Q;++i){
		string type;
		cin >> type;
		if(type == "BOOK"){
			long long time;
			string hotel_name;
			int client_id;
			int room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			bm.book(time, hotel_name, client_id, room_count);
		}
		if (type == "CLIENTS"){
			string hotel_name;
			cin >> hotel_name;
			cout << bm.clients_last_hour(hotel_name) << "\n";
		}
		if (type == "ROOMS"){
			string hotel_name;
			cin >> hotel_name;
			cout << bm.rooms_last_hour(hotel_name) << "\n";
		}
	}
	return 0;
}
