#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class Person {
public:
Person(const string & newfirstname, const string & newlastname, int birth) : birthyear(birth)
  {
      Persons_Map[birth].first = newfirstname;
      Persons_Map[birth].second = newlastname;
  }

  void ChangeFirstName(int year, const string& first_name) {
      // добавить факт изменения имени на first_name в год year
    if (year < birthyear) return;
    if(Persons_Map.count(year) == 0)Persons_Map[year].second = "";
    Persons_Map[year].first = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
      // добавить факт изменения имени на first_name в год year
    if (year < birthyear) return;
    if(Persons_Map.count(year) == 0)Persons_Map[year].first = "";
    Persons_Map[year].second = last_name;
  }
  string GetFullName(int year) const {
      // получить имя и фамилию по состоянию на конец года year
    if (year < birthyear) return "No person";
    if (year < Persons_Map.begin()->first || Persons_Map.empty()) return "Incognito";
    string firstname = "", lastname = "";
    for (auto it = Persons_Map.begin(); it != Persons_Map.end(); it++)
    {
        if (year < it->first) break;
        if(it->second.first != "")firstname = it->second.first;
        if(it->second.second != "")lastname = it->second.second;
    }
    if (firstname == "") return lastname+" with unknown first name";
    if (lastname == "") return firstname+" with unknown last name";
    return firstname + " " + lastname;
  }
  string GetFullNameWithHistory(int year) const {
      // получить все имена и фамилии по состоянию на конец года year
      if (year < birthyear) return "No person";
      if (year < Persons_Map.begin()->first || Persons_Map.empty()) return "Incognito";
      string firstname = "", lastname = "";
      vector<string> history_of_firstname, history_of_lastname;
      for (auto it = Persons_Map.begin(); it != Persons_Map.end(); it++)
      {
          if (year < it->first) break;
          if(it->second.first != "")
          {
              if(firstname != "" && firstname != it->second.first)history_of_firstname.emplace_back(firstname);
              firstname = it->second.first;
          }
          if(it->second.second != "")
          {
              if(lastname != "" && lastname != it->second.second)history_of_lastname.emplace_back(lastname);
              lastname = it->second.second;
          }
      }

      firstname += AddHistory(history_of_firstname);
      lastname += AddHistory(history_of_lastname);
      if (firstname == "") return lastname+" with unknown first name";
      if (lastname == "") return firstname+" with unknown last name";
      return firstname + " " + lastname;
  }
private:
  string AddHistory(const vector<string> &historyVector) const  {
      string history = "";
      if (!historyVector.empty())
      {
          history +=" (";
          for (auto oneof = historyVector.rbegin(); oneof != historyVector.rend(); oneof++)
          {
            if (history.length()>2) history += ", ";
            history += *oneof;
          }
          history +=")";
      }
      return history;
  }
// FIELDS
  map<int,pair<string,string>> Persons_Map;
  int birthyear;
};