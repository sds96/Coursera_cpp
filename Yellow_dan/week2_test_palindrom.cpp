#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

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

void Correct(){
	Assert(IsPalindrom("level"), "level");
	Assert(IsPalindrom("aaaaaaaaaaa"), "aaaaaaaaaaa");
	Assert(IsPalindrom("ava"), "ava");
	Assert(IsPalindrom("3"), "3");
	Assert(IsPalindrom("w"), "w");
	Assert(IsPalindrom(" "), "1 probel");
	Assert(IsPalindrom("  "), "2 probel");
	Assert(IsPalindrom("   "), "3 probel");
	Assert(IsPalindrom(""), "empty string");
	Assert(IsPalindrom("w w w"), "w w w");
	Assert(IsPalindrom("w   w   w"), "w   w   w");
	Assert(IsPalindrom("aaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaa"), "aaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaa");
}

void InCorrect(){
	Assert(!IsPalindrom(" ava"), "porbel i ava");
	Assert(!IsPalindrom("vava"), "vava");
	Assert(!IsPalindrom("kek "), "kek probel");
	Assert(!IsPalindrom("w  w w"), "w  w w");
	Assert(!IsPalindrom("w w       w"), "w w       w");
	Assert(!IsPalindrom("XabbaY"), "XabbaY is not a palindrome");
	Assert(!IsPalindrom("aaaaaaaaaaaaaaaaaaaaaab2aaaaaaaaaaaaaaaaaaaaaa"), "aaaaaaaaaaaaaaaaaaaaaab2aaaaaaaaaaaaaaaaaaaaaa");
	Assert(!IsPalindrom("madam level"), "madam level");
}


int main() {
  TestRunner runner;
  runner.RunTest(Correct, "Correct");
  runner.RunTest(InCorrect, "InCorrect");
  // добавьте сюда свои тесты
  return 0;
}
