#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "date.h"


template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, std::pair<T, U> p)
{
    out << p.first << " " << p.second;
    return out;
}

class Database {
public:
  void Add(const Date& date, const std::string& event);

  bool DeleteEvent(const Date& date, const std::string& event);

  int DeleteDate(const Date& date);

  std::set<std::string> Find(const Date& date) const;

  void Print(std::ostream& os) const;

  std::string Last(const Date& date) const;

  template<typename PredFunc>
  std::vector<std::pair<Date, std::string>> FindIf(PredFunc predicate) const
       {
           std::vector<std::pair<Date, std::string>> Result;
           std::for_each(storage2.begin(),
                         storage2.end(),
                         [&predicate, &Result]
                         (const std::pair<const Date, std::vector<std::string>>& EventsForDate) mutable
           {
                 std::for_each(EventsForDate.second.begin(),
                               EventsForDate.second.end(),
                               [&predicate, &EventsForDate, &Result] (const std::string& event)
                 {
                     if (predicate(EventsForDate.first, event)) Result.emplace_back(EventsForDate.first, event);
                 });
           });
           return Result;
       }

  template<typename PredFunc> int RemoveIf(PredFunc predicate)
  {
      int DeletedCount = 0;
      std::for_each(storage2.begin(),
                    storage2.end(),
                    [&predicate, &DeletedCount]
                    (std::pair<const Date,
                               std::vector<std::string>>
                                          & EventsForDate) mutable
      {
            DeletedCount += EventsForDate.second.size();
            auto it = std::stable_partition(EventsForDate.second.begin(),
                                            EventsForDate.second.end(),
                                            [&EventsForDate, &predicate] (const auto& element)
            {
                return !predicate(EventsForDate.first, element);
            });
            EventsForDate.second.erase(it, EventsForDate.second.end());
            DeletedCount -= EventsForDate.second.size();
      });
      for (auto it = storage2.begin(); it != storage2.end();)
      {
          if (it->second.empty()) {
              storage2.erase(it++);
          } else {
              ++it;
          }
      }
      storage.clear();
      for (const auto& i : storage2){
    	  for (const auto& k: i.second){
        	  storage[i.first].insert(k);
    	  }
      }
      return DeletedCount;
  }

private:
  std::map<Date, std::set<std::string>> storage;  // ������������
  std::map<Date, std::vector<std::string>> storage2;  // ������� ���������� ���
};

#endif /* DATABASE_H_ */
