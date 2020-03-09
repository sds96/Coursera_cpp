#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
}

void quadroTest(){
	AssertEqual(GetDistinctRealRootCount(1,0,0), 1, "100");
	AssertEqual(GetDistinctRealRootCount(1,0,-4), 2, "10-4");
	AssertEqual(GetDistinctRealRootCount(1,0,4), 0, "104");
}

void linearTest(){
	AssertEqual(GetDistinctRealRootCount(0,1,0), 1, "010");
	AssertEqual(GetDistinctRealRootCount(0,1,2), 1, "012");
	AssertEqual(GetDistinctRealRootCount(0,-1,3), 1, "0-13");
	AssertEqual(GetDistinctRealRootCount(0,0,3), 0, "003");
}

void FullTest(){
	AssertEqual(GetDistinctRealRootCount(1, 3, 2), 2, "132");
	AssertEqual(GetDistinctRealRootCount(-1,3,2), 2, "-132");
	AssertEqual(GetDistinctRealRootCount(1,3,5), 0, "135");
	AssertEqual(GetDistinctRealRootCount(1,3,-5), 2, "13-5");
}

int main() {

		TestRunner runner;
  runner.RunTest(quadroTest, "quadroTest");
  runner.RunTest(linearTest, "linearTest");
  runner.RunTest(FullTest, "FullTest");

  // добавьте сюда свои тесты
  return 0;
}
