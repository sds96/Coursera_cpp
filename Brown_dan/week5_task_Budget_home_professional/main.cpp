#include <iostream>
#include <ctime>
#include <string_view>
#include "test_runner.h"
#include "profile.h"
#include <sstream>

using namespace std;

class Date{
public:
	int year_;
	int month_;
	int day_;

	Date(int y, int m, int d) : year_(y), month_(m), day_(d)
	{};

	Date(string date){
		stringstream ss(date);
		ss >> year_;
		ss.ignore(1);
		ss >> month_;
		ss.ignore(1);
		ss >> day_;
	};

    string toString() const {
	string yearString  = to_string(year_);
	string monthString = to_string(month_);
	string dayString   = to_string(day_);
	if (monthString.size() == 1)
		monthString = "0" + monthString;

	if (dayString.size() == 1)
		dayString = "0" + dayString;

	return yearString + "-" + monthString + "-" + dayString;
    }

	time_t AsTimestamp() const {
	  tm t;
	  t.tm_sec   = 0;
	  t.tm_min   = 0;
	  t.tm_hour  = 0;
	  t.tm_mday  = day_;
	  t.tm_mon   = month_ - 1;
	  t.tm_year  = year_ - 1900;
	  t.tm_isdst = 0;
	  return mktime(&t);
	}
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  const time_t timestamp_to = date_to.AsTimestamp();
  const time_t timestamp_from = date_from.AsTimestamp();
  static const int SECONDS_IN_DAY = 60 * 60 * 24;
  return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
};

size_t Date_to_ind(const Date& date){
	return ComputeDaysDiff(date, Date("2000-01-01"));
}

class BudgetManager{
private:
	vector<double> budget;
	vector<double> spend;
public:
	BudgetManager(){
		budget.resize(36526);
		spend.resize(36526);
	}

	void Earn(const Date& from, const Date& to, double value){
		double value_per_day = value / (ComputeDaysDiff(to, from) + 1);
		size_t f = Date_to_ind(from);
		size_t l = Date_to_ind(to);
		for(size_t i = f; i <= l; ++i){
			budget[i] += value_per_day;
		}
	};

	void PayTax(const Date& from, const Date& to, int percent){
		size_t f = Date_to_ind(from);
		size_t l = Date_to_ind(to);
		double tax_rate = (100.0-percent)/100.0;
		for(size_t i = f; i <= l; ++i){
			budget[i] *= tax_rate;
		}
	};

	void Spend(const Date& from, const Date& to, double value){
		double value_per_day = value / (ComputeDaysDiff(to, from) + 1);
		size_t f = Date_to_ind(from);
		size_t l = Date_to_ind(to);
		for(size_t i = f; i <= l; ++i){
			spend[i] += value_per_day;
		}
	}

	double ComputeIncome(const Date& from, const Date& to){
		double income(0);
		size_t f = Date_to_ind(from);
		size_t l = Date_to_ind(to);
		for(size_t i = f; i <= l; ++i){
			income += budget[i] - spend[i];
		}
		return income;
	};

};

void ProcessQuerry(BudgetManager& bm, istream& is, ostream& os){
	int Q;
	is >> Q;
	while (Q>0){
        string command, fromDate, toDate;
        is >> command >> fromDate >> toDate;
        if (command == "Earn") {
            double value;
            is >> value;
            bm.Earn(Date(fromDate), Date(toDate), value);
        } else if (command == "ComputeIncome") {
            os << bm.ComputeIncome(Date(fromDate), Date(toDate)) << endl;
        } else if (command == "PayTax") {
        	double percent;
			is >> percent;
            bm.PayTax(Date(fromDate), Date(toDate), percent);
        } else if (command == "Spend"){
        	double value;
			is >> value;
			bm.Spend(Date(fromDate), Date(toDate), value);
        }
        Q--;
	}
}

void TestEarn(){
	BudgetManager bm;
	bm.Earn(Date("2000-01-02"), Date("2000-01-06"), 20);
	double income = bm.ComputeIncome(Date("2000-01-01"), Date("2001-01-01"));
	ASSERT_EQUAL(income, 20);
	income = bm.ComputeIncome(Date("2000-01-02"), Date("2000-01-02"));
	ASSERT_EQUAL(income, 4);
}

void Test1(){
	BudgetManager bm;
	istringstream is("8 \n "
			"Earn 2000-01-02 2000-01-06 20 \n"
			"ComputeIncome 2000-01-01 2001-01-01 \n"
			"PayTax 2000-01-02 2000-01-03 13\n"
			"ComputeIncome 2000-01-01 2001-01-01 \n"
			"Earn 2000-01-03 2000-01-03 10 \n"
			"ComputeIncome 2000-01-01 2001-01-01 \n"
			"PayTax 2000-01-03 2000-01-03 13\n"
			"ComputeIncome 2000-01-01 2001-01-01");
	ostringstream os;
	ProcessQuerry(bm, is, os);
	string result ("20\n"
			"18.96\n"
			"28.96\n"
			"27.2076\n");
	ASSERT_EQUAL(os.str(), result);
}

void Test2(){
	BudgetManager bm;
	istringstream is("8 \n "
			"Earn 2000-01-02 2000-01-06 20 \n"
			"ComputeIncome 2000-01-01 2001-01-01 \n"
			"PayTax 2000-01-02 2000-01-03 13\n"
			"ComputeIncome 2000-01-01 2001-01-01 \n"
			"Spend 2000-12-30 2001-01-02 14 \n"
			"ComputeIncome 2000-01-01 2001-01-01 \n"
			"PayTax 2000-12-30 2000-12-30 13 \n"
			"ComputeIncome 2000-01-01 2001-01-01");
	ostringstream os;
	ProcessQuerry(bm, is, os);
	string result ("20\n"
			"18.96\n"
			"8.46\n"
			"8.46\n");
	ASSERT_EQUAL(os.str(), result);
}

int main(){
	//TestRunner tr;
	//RUN_TEST(tr, TestEarn);
	//RUN_TEST(tr, Test1);
	//RUN_TEST(tr, Test2);

	BudgetManager bm;
	cout.precision(25);
	ProcessQuerry(bm, cin, cout);
	return 0;
}



