#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
/*
enum class Gender{
	FEMALE,
	MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};
*/

void PrintStats(vector<Person> persons) {
    // ѕреобразуем пор€док людей к следующему:
    // females(empl., unempl.) - > males( empl., unempl.)
    auto fem_end = partition(
        begin(persons), end(persons), [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    auto employed_fem_end = partition(
        begin(persons), fem_end, [](const Person& p) {
            return p.is_employed;
        }
    );
    auto employed_males_end = partition(
        fem_end, end(persons), [](const Person& p) {
            return p.is_employed;
        }
    );

    // “еперь интересующие нас группы наход€тс€ в векторе непрерывно
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons))          << endl;
    cout << "Median age for females = "
         << ComputeMedianAge(begin(persons), fem_end)           << endl;
    cout << "Median age for males = "
         << ComputeMedianAge(fem_end, end(persons))             << endl;
    cout << "Median age for employed females = "
         << ComputeMedianAge(begin(persons),  employed_fem_end) << endl;
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(employed_fem_end, fem_end)     << endl;
    cout << "Median age for employed males = "
         << ComputeMedianAge(fem_end, employed_males_end)       << endl;
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(employed_males_end, end(persons))      << endl;
}
