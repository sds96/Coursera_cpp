#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

string ParseEvent(istream& is) {
  bool first_spaces = true;
  while (first_spaces){
	  if(is.peek() == ' ')
		  is.ignore(1);
	  else
		  first_spaces = false;
  }
  string event;
  getline(is, event);
  return event;
}

void TestAll();

int main() {
  TestAll();
  Database db;


  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestLast(){
	Database db;
	  vector<string> s{
								  "Add 2017-01-01 New Year \n",
								  "Add 2017-03-08 Holiday \n",
								  "Add 2017-01-01 Holiday \n",
								  "Last 2016-12-31 \n",
								  "Last 2017-01-01 \n",
								  "Last 2017-06-01 \n",
								  "Add 2017-05-09 Holiday"};
	  ostringstream oss;
	  for(auto el:s){
	  istringstream is(el);
	  string command;
	      is >> command;
	      if (command == "Add") {
	        const auto date = ParseDate(is);
	        const auto event = ParseEvent(is);
	        db.Add(date, event);
	      } else if (command == "Last") {
	          try {
	              oss << db.Last(ParseDate(is)) << endl;
	          } catch (invalid_argument&) {
	              oss << "No entries" << endl;
	          }
	      }
	  }
	  string tmp = 	"No entries\n2017-01-01 Holiday \n2017-03-08 Holiday \n";
	  AssertEqual(tmp, oss.str(), "Last_from_coursera");
}

void TestAdd(){
	Database db;
	vector<string> s{ "Add   2017-01-01 Holiday \n", "Add 2017-03-08 Holiday \n",
		  	  	  	  	  	  	  "Add 2017-1-1 New Year \n", "Add 2017-1-1 New Year \n", "Print \n"};
	ostringstream oss;
	for (const auto& el: s){
		istringstream is(el);
		string command;
		      is >> command;
		      if (command == "Add") {
		        const auto date = ParseDate(is);
		        const auto event = ParseEvent(is);
		        db.Add(date, event);
		      } else if (command == "Print") {
		        db.Print(oss);
		      }
	}
	string tmp = "2017-01-01 Holiday \n2017-01-01 New Year \n2017-03-08 Holiday \n";
	AssertEqual(tmp, oss.str(), "Add_from_coursera");
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestAdd, "TestAdd");
  tr.RunTest(TestLast, "TestLast");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
