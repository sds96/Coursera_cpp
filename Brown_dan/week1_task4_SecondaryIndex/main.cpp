#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>
#include <stdexcept>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

struct Iterators{
	multimap<int, list<Record>::iterator>::iterator karma_it;
	multimap<int, list<Record>::iterator>::iterator timestamp_it;
	multimap<string, list<Record>::iterator>::iterator user_it;
};

// Реализуйте этот класс
class Database {
private:
	list<Record> m_records;
	unordered_map<string, list<Record>::iterator> id_rec;
	multimap<int, list<Record>::iterator> karma_map;
	multimap<int, list<Record>::iterator> timestamp_map;
	multimap<string, list<Record>::iterator> user_map;

	unordered_map<string, Iterators> iters;
public:
  bool Put(const Record& record){
	  if(id_rec.find(record.id) == id_rec.end()){
		  m_records.push_front(record);
		  id_rec[record.id] = m_records.begin();
		  const auto k = karma_map.insert({record.karma, m_records.begin()});
		  const auto t = timestamp_map.insert({record.timestamp, m_records.begin()});
		  const auto u = user_map.insert({record.user, m_records.begin()});
		  iters.insert({record.id, {k, t, u}});
		  return true;
	  }else{
		  return false;
	  }
  };
  const Record* GetById(const string& id) const{
	    try
	    {
			return &(*id_rec.at(id));
	    }
	    catch (std::out_of_range&)
	    {
	        return nullptr;
	    }
  };
  bool Erase(const string& id){
	  auto f = id_rec.find(id);
	  if(f != id_rec.end()){
		  const Iterators iterat = iters.at(f->first);
		  karma_map.erase(iterat.karma_it);
		  timestamp_map.erase(iterat.timestamp_it);
		  user_map.erase(iterat.user_it);

		  id_rec.erase(f);
		  m_records.erase(f->second);
		  return true;
	  }else{
		  return false;
	  }
  };

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
	    auto lower = timestamp_map.lower_bound(low);
	    const auto upper = timestamp_map.upper_bound(high);
		while (lower != upper && callback(*lower->second))
			++lower;
  };

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
	    auto lower = karma_map.lower_bound(low);
	    const auto upper = karma_map.upper_bound(high);
		while (lower != upper && callback(*lower->second))
			++lower;
  };

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
	    auto [first, last] = user_map.equal_range(user);
		while (first != last && callback(*first->second))
			++first;
  };
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
