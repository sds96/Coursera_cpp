#include "database.h"
#include <utility>
#include <vector>
#include <algorithm>
#include "date.h"
#include <map>
#include <set>

using namespace std;

  void Database::Add(const Date& date, const string& event) {
    if(storage[date].insert(event).second)
    	storage2[date].push_back(event);
  }

  bool Database::DeleteEvent(const Date& date, const string& event) {
    if (storage.count(date) > 0 && storage[date].count(event) > 0) {
      storage[date].erase(event);
      return true;
    }
    return false;
  }

  int Database::DeleteDate(const Date& date) {
    if (storage.count(date) == 0) {
      return 0;
    } else {
      const int event_count = storage[date].size();
      storage.erase(date);
      return event_count;
    }
  }

  set<string> Database::Find(const Date& date) const {
    if (storage.count(date) > 0) {
      return storage.at(date);
    } else {
      return {};
    }
  }

  void Database::Print(ostream& os) const {
    for (const auto& item : storage2) {
      for (const string& event : item.second) {
        os << item.first << " " << event << "\n";
      }
    }
  }

  string Database::Last(const Date& date) const{
	  auto it = storage2.upper_bound(date);
	  if(it != storage2.begin()){
		  ostringstream oss;
		  oss << prev(it)->first << " ";
		  return  oss.str() + prev(it)->second.back();
	  } else
		  throw invalid_argument("");
  }
