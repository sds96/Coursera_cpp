#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <sstream>

class Date{
public:
	Date(int new_year, int new_month, int new_day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	friend std::istream& operator>>(std::istream& in, Date& date);
	friend bool operator==(const Date& lhs, const Date& rhs);
	friend bool operator<(const Date& lhs, const Date& rhs);
private:
	  int year;
	  int month;
	  int day;
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& stream, const Date& date);

Date ParseDate(std::istringstream& date_stream);

Date ParseDate(std::istream& date_stream);
#endif /* DATE_H_ */
