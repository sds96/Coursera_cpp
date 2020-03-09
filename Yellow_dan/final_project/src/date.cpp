#include "date.h"
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

bool operator==(const Date& lhs, const Date& rhs)
{
    if ( tie(lhs.year,lhs.month,lhs.day) == tie(rhs.year,rhs.month,rhs.day) )
        return true;
    else
        return false;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if ( tie(lhs.year,lhs.month,lhs.day) < tie(rhs.year,rhs.month,rhs.day) )
        return true;
    else
        return false;
}

bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs);}
bool operator<=(const Date& lhs, const Date& rhs) { return (lhs < rhs || lhs == rhs);}
bool operator>(const Date& lhs, const Date& rhs) { return !(lhs <= rhs);}
bool operator>=(const Date& lhs, const Date& rhs) { return !(lhs < rhs);}

  Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }

  int Date::GetYear() const {
    return year;
  }
  int Date::GetMonth() const {
    return month;
  }
  int Date::GetDay() const {
    return day;
  }

// ���� ����� �� ��������� ���������� � ������ �������
ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

Date ParseDate(istringstream& date_stream) {
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);

  if (!ok) {
    throw logic_error("Wrong date format: " + date_stream.str());
  }
  return Date(year, month, day);
}

Date ParseDate(istream& date_stream) {
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);

  if (!ok) {
    throw logic_error("Wrong date format: ??");
  }
  return Date(year, month, day);
}
