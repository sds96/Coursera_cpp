#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

void CheckNext(stringstream& is)
{
    if (is.peek() != '-') {
        throw exception();
    }
    is.ignore(1);
}

class Date {
public:
  int GetYear() const {return year;};
  int GetMonth() const {return month;};
  int GetDay() const {return day;};
  friend istream& operator>>(istream& is, Date& rhs);
private:
  int year;
  int month;
  int day;
};

ostream& operator<<(ostream& out, const Date& date)
{
    out << setw(4) << setfill('0') << date.GetYear() << '-'
        << setw(2) << setfill('0') << date.GetMonth() << '-'
        << setw(2) << setfill('0') << date.GetDay();
    return out;
}

istream& operator>>(istream& is, Date& rhs){
	string input;
	is >> input;
	stringstream InputStream(input);
	try{
		InputStream >> rhs.year;
		CheckNext(InputStream);
		InputStream >> rhs.month;
		CheckNext(InputStream);
		if(!(InputStream >> rhs.day))throw exception();
		if (!InputStream.eof()) throw exception();
		if (rhs.month <1 || rhs.month > 12) throw invalid_argument("Month value is invalid: " + to_string(rhs.month));
		if (rhs.day <1 || rhs.day > 31) throw invalid_argument("Day value is invalid: " + to_string(rhs.day));
	}
	catch (const invalid_argument& ex){
		throw invalid_argument(ex.what());
	}
	catch (const exception&) {
		throw invalid_argument("Wrong date format: "+input);
	}
	return is;
}

bool operator<(const Date& lhs, const Date& rhs){
	if(lhs.GetYear()<rhs.GetYear())return true;
	if(lhs.GetYear()>rhs.GetYear())return false;
	if(lhs.GetMonth()<rhs.GetMonth())return true;
	if(lhs.GetMonth()>rhs.GetMonth())return false;
	if(lhs.GetDay()<rhs.GetDay())return true;
	return false;
};

class Database {
public:
  void AddEvent(const Date& date, const string& event){
	  EventMap[date].insert(event);
  };
  bool DeleteEvent(const Date& date, const string& event){
	    if(EventMap.count(date))
	    {
	        if(EventMap.at(date).count(event))
	        {
	            EventMap.at(date).erase(event);
	            if(EventMap.at(date).empty())EventMap.erase(date);
	            return true;
	        }
	    }
	    return false;
  };
  int  DeleteDate(const Date& date){
	  if(EventMap.count(date))
	      {
	          int DeletedEventsCount = static_cast<int>(EventMap.at(date).size());
	          EventMap.erase(date);
	          return DeletedEventsCount;
	      }
	  return 0;
  };

  set<string> Find(const Date& date) const{
	  if(EventMap.count(date)){
		  return EventMap.at(date);
	  } else
		  return set<string>();
  };

  void Print() const{
	  for (auto& e : EventMap){
		  for (auto& ev : e.second){
			  cout << e.first << " " << ev <<endl;
		  }
	  }
  };

private:
  map<Date, set<string>> EventMap;
};

int main() {
  Database db;
  string command;
  while (getline(cin, command)) {
	  if(command.length() == 0) continue;
	  stringstream commandStream(command);		// делаем поток для удобства парса
	  string commandName;
	  commandStream >> commandName;				// хватаем название команды
      if(commandName != "Add" &&
         commandName != "Del" &&
         commandName != "Find" &&
         commandName != "Print") {cout << "Unknown command: " << commandName << endl; return 0;}
	  if (commandName == "Add"){
		  Date date;
		  string event;
		  try{
			  commandStream >> date >> event;		// берем из потока дату и событие
		  }
		  catch(const invalid_argument& exe){
			  cout << exe.what();
			  return 0;
		  }
		  db.AddEvent(date, event);
	  }
	  if(commandName == "Del"){
		  Date date;
		  string event;
		  try{
		  	commandStream >> date >> event;		// берем из потока дату и событие
		  }
		  catch(const invalid_argument& exe){
		  	cout << exe.what();
		  	return 0;
		  }
		  if(event.length() == 0){ 		// если нужно удалить всю дату
			  cout << "Deleted " << db.DeleteDate(date)<< " events" << endl;
		  }
		  else {		// удалить конкретное событие
			  if(db.DeleteEvent(date, event)) cout<< "Deleted successfully" <<endl;
			  else cout << "Event not found" <<endl;
		  }
	  }
	  if(commandName == "Find"){
		  Date date;
		  try{
			  commandStream >> date;	// берем из потока дату
		  }
		  catch(const invalid_argument& exe){
			  cout << exe.what();
			  return 0;
		  }
		  for(auto& el : db.Find(date)){
			  cout << el <<endl;
		  }
	  }
	  if(commandName == "Print"){
		  db.Print();
	  }
  }

  return 0;
}
