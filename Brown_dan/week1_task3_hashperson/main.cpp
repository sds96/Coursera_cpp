#include "test_runner.h"
#include <limits>
#include <random>
#include <unordered_set>

using namespace std;

struct Address {
  string city, street;
  int building;

  bool operator==(const Address& other) const {
    return (city == other.city) &&
    		(street == other.street) &&
			(building == other.building);
  }
};

struct Person {
  string name;
  int height;
  double weight;
  Address address;

  bool operator==(const Person& other) const {
    return (name == other.name) &&
    		(height == other.height) &&
			(weight == other.weight) &&
			(address == other.address);
  }
};

struct AddressHasher {
  size_t operator() (const Address& a) const {
	  size_t r1 = h1(a.city);
	  size_t r2 = h1(a.street);
	  size_t r3 = h2(a.building);
	  size_t num = 2'946'901;
	  size_t ret = num*num*r1 + num*r2 + r3;
	  return ret;
  }

  hash<string> h1;
  hash<int> h2;
};

struct PersonHasher {
  size_t operator() (const Person& p) const {
	  size_t r1 = h1(p.name);
	  size_t r2 = h2(p.height);
	  size_t r3 = h3(p.weight);
	  size_t r4 = h4(p.address);
	  size_t num = 2'946'901;
	  size_t ret = num*num*num*r1 + num*num*r2 + num*r3 + r4;
	  return ret;
  }

  hash<string> h1;
  hash<int> h2;
  hash<double> h3;
  AddressHasher h4;
};

// ������������� ��������:
// $ sort -R /usr/share/dict/propernames | head -n 100
//
// http://www.freebsd.org/cgi/cvsweb.cgi/~checkout~/src/share/dict/propernames
const vector<string> WORDS = {
  "Kieran", "Jong", "Jisheng", "Vickie", "Adam", "Simon", "Lance",
  "Everett", "Bryan", "Timothy", "Daren", "Emmett", "Edwin", "List",
  "Sharon", "Trying", "Dan", "Saad", "Kamiya", "Nikolai", "Del",
  "Casper", "Arthur", "Mac", "Rajesh", "Belinda", "Robin", "Lenora",
  "Carisa", "Penny", "Sabrina", "Ofer", "Suzanne", "Pria", "Magnus",
  "Ralph", "Cathrin", "Phill", "Alex", "Reinhard", "Marsh", "Tandy",
  "Mongo", "Matthieu", "Sundaresan", "Piotr", "Ramneek", "Lynne", "Erwin",
  "Edgar", "Srikanth", "Kimberly", "Jingbai", "Lui", "Jussi", "Wilmer",
  "Stuart", "Grant", "Hotta", "Stan", "Samir", "Ramadoss", "Narendra",
  "Gill", "Jeff", "Raul", "Ken", "Rahul", "Max", "Agatha",
  "Elizabeth", "Tai", "Ellen", "Matt", "Ian", "Toerless", "Naomi",
  "Rodent", "Terrance", "Ethan", "Florian", "Rik", "Stanislaw", "Mott",
  "Charlie", "Marguerite", "Hitoshi", "Panacea", "Dieter", "Randell", "Earle",
  "Rajiv", "Ted", "Mann", "Bobbie", "Pat", "Olivier", "Harmon",
  "Raman", "Justin"
};

void TestSmoke() {
  vector<Person> points = {
    {"John", 180, 82.5, {"London", "Baker St", 221}},
    {"Sherlock", 190, 75.3, {"London", "Baker St", 221}},
  };

  unordered_set<Person, PersonHasher> point_set;
  for (const auto& point : points) {
    point_set.insert(point);
  }

  ASSERT_EQUAL(points.size(), point_set.size());
  for (const auto& point : points) {
    ASSERT_EQUAL(point_set.count(point), static_cast<size_t>(1));
  }
}

void TestPurity() {
  Person person = {"John", 180, 82.5, {"London", "Baker St", 221}};
  PersonHasher hasher;

  auto hash = hasher(person);
  for (size_t t = 0; t < 100; ++t) {
    ASSERT_EQUAL(hasher(person), hash);
  }
};

void TestDistribution() {
  auto seed = 42;
  mt19937 gen(seed);

  uniform_int_distribution<int> height_dist(150, 200);
  uniform_int_distribution<int> weight_dist(100, 240);  // [50, 120]
  uniform_int_distribution<int> building_dist(1, 300);
  uniform_int_distribution<int> word_dist(0, WORDS.size() - 1);

  PersonHasher hasher;

  // �������� ����� ������� �� ����� ������� ������� ������
  // (unordered_set, unordered_map ���������� ������� ����� �������
  // � ����������� GCC � Clang, ��� ��������� ����� �������
  // ��������� ��������� �� ����������� ���-�������� � ���� �����������)
  const size_t num_buckets = 2053;

  // �� �����, ����� ����� ����� � ������� ���� ~100'000
  const size_t perfect_bucket_size = 50;
  const size_t num_points = num_buckets * perfect_bucket_size;
  vector<size_t> buckets(num_buckets);
  for (size_t t = 0; t < num_points; ++t) {
    Person person;
    person.name = WORDS[word_dist(gen)];
    person.height = height_dist(gen);
    person.weight = weight_dist(gen) * 0.5;
    person.address.city = WORDS[word_dist(gen)];
    person.address.street = WORDS[word_dist(gen)];
    person.address.building = building_dist(gen);
    ++buckets[hasher(person) % num_buckets];
  }

  // ���������� �������:
  // https://en.wikipedia.org/wiki/Pearson's_chi-squared_test
  //
  // ��������� ����� ������������� ������������� ����� ����� ���������
  // ��������, �� ��� �� ������� ��� ������� �������������� �������������
  double pearson_stat = 0;
  for (auto bucket_size : buckets) {
    size_t size_diff = bucket_size - perfect_bucket_size;
    pearson_stat +=
        size_diff * size_diff / static_cast<double>(perfect_bucket_size);
  }

  // ��������� ������������� ������������� ������� �������� �������
  // �� �������������� ����������� 0.95:
  //
  // ���� ���������� ������ ++buckets[hasher(person) % num_buckets]
  // ��������� ++buckets[gen() % num_buckets], �� � ������������ 95%
  // ASSERT ���� ���������� �������,
  //
  // �.�. ���������� ������� �������������� ������������ �� chi^2
  // � ������ �������� �������, ������ num_buckets - 1,
  // � 95 ���������� ����� ������������� �����:
  // >>> scipy.stats.chi2.ppf(0.95, 2052)
  const double critical_value = 2158.4981036918693;
  ASSERT(pearson_stat < critical_value);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestPurity);
  RUN_TEST(tr, TestDistribution);

  return 0;
}