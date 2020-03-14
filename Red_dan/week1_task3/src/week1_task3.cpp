#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <tuple>

using namespace std;

#define UPDATE_FIELD(ticket, field, values) {   \
    map<string, string>::const_iterator it;     \
    it = values.find(#field);                   \
    if (it != values.end()) {                   \
        istringstream in(it->second);           \
        in >> ticket.field;                     \
    }                                           \
}


bool operator<(const Date& lhs, const Date& rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

ostream& operator<<(ostream& out, const Date& date)
{
    out << setfill('0') << setw(4) << date.year << "-"
        << setfill('0') << setw(2) << date.month << "-"
        << setfill('0') << setw(2) << date.day;
    return out;
}

void EnsureNextSymbol(stringstream& in, const string& input, const char& symbol)
{
    if (in.peek() != symbol) {
        throw invalid_argument("Wrong format: "+input);
    }
    in.ignore(1);
}

istream& operator>>(istream& in, Date& date)
{
    string input;
    in >> input;
    stringstream InputStream(input);
    InputStream >> date.year;
    EnsureNextSymbol(InputStream, input, '-');
    InputStream >> date.month;
    EnsureNextSymbol(InputStream, input, '-');
    if(!(InputStream >> date.day))throw invalid_argument("Wrong date format: "+input);
    if (!InputStream.eof()) throw invalid_argument("Wrong date format: "+input);
    if (date.month < 1 || date.month > 12) throw invalid_argument("Month value is invalid: "+to_string(date.month));
    if (date.day < 1 || date.day > 31) throw invalid_argument("Day value is invalid: "+to_string(date.day));
    return in;
}


bool operator<(const Time& lhs, const Time& rhs)
{
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs)
{
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& out, const Time& date)
{
    out << setfill('0') << setw(2) << date.hours << ":"
        << setfill('0') << setw(2) << date.minutes;
    return out;
}

istream& operator>>(istream& in, Time& time)
{
    string input;
    in >> input;
    stringstream InputStream(input);
    InputStream >> time.hours;
    EnsureNextSymbol(InputStream, input, ':');
    if(!(InputStream >> time.minutes))throw invalid_argument("Wrong time format: "+input);
    if (!InputStream.eof()) throw invalid_argument("Wrong time format: "+input);
    if (time.hours < 0 || time.hours >= 24) throw invalid_argument("Hours value is invalid: "+to_string(time.hours));
    if (time.minutes < 0 || time.minutes >= 60) throw invalid_argument("Minutes value is invalid: "+to_string(time.minutes));
    return in;
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
