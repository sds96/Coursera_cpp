#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>

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

void simpletest(){
	Rational r;
	
	AssertEqual(r.Numerator(), 0, "default");
	AssertEqual(r.Denominator(), 1, "default");
	
	AssertEqual(Rational(-0, 3).Numerator(), 0, "03 = 01");
	AssertEqual(Rational(-0, 3).Denominator(), 1, "-03 = 01");
	
	AssertEqual(Rational(0, -1).Numerator(), 0,"0/-1 ");
	AssertEqual(Rational(0, -1).Denominator(), 1," 0/-1");
	
	AssertEqual(Rational(-numeric_limits<int>::max(), numeric_limits<int>::max()).Numerator(), -1, "limits");
	AssertEqual(Rational(numeric_limits<int>::max(), -numeric_limits<int>::max()).Denominator(), 1, "limits");
	AssertEqual(Rational(-numeric_limits<int>::max(), 1).Numerator(), -numeric_limits<int>::max(), "limits");
	AssertEqual(Rational(0, numeric_limits<int>::max()).Denominator(), 1, "limits");
	
	AssertEqual(Rational(3,6).Numerator(), 1, "3/6 == 1/2");
	AssertEqual(Rational(3,6).Denominator(), 2, "3/6 == 1/2");
	
	AssertEqual(Rational(10, -5).Numerator(), -2, "10/-5 == -2/1");
	AssertEqual(Rational(10, -5).Denominator(), 1, "10/-5 == -2/1");
	
	AssertEqual(Rational(-10,-2).Numerator(), 5, "-10/2 == 5/1");
	AssertEqual(Rational(-10,-2).Denominator(), 1, "-10/2 == 5/1");
	
	AssertEqual(Rational(-7, 3).Numerator(), -7, "-7/3 = -7");
	AssertEqual(Rational(-7, 3).Denominator(), 3, "-7/3 = 3");
	
	AssertEqual(Rational(7, -3).Numerator(), -7, "-7/3 = -7");
	AssertEqual(Rational(7, -3).Denominator(), 3, "-7/3 = 3");
}

/*void calctest(){
	AssertEqual(Rational(1,2) * Rational(2,1), Rational(1,1), "* = 1");
	AssertEqual(Rational(5,3) * Rational(4,1), Rational(20,3), "* = 20/3");
	AssertEqual(Rational(5,2) * Rational(10,3), Rational(25, 3), "* = 25/3");
	
	AssertEqual(Rational(1,2) + Rational(2,3), Rational(5,6), "+ = 5/6");
	AssertEqual(Rational(4,3) - Rational(5,3), Rational(-1,3), "- = -1/3");
	AssertEqual(Rational(1,-2) + Rational(1,2), Rational(0,1), "-+ = 0");
	
	AssertEqual(Rational(3, 4) / Rational(3, -4), Rational(-1,1), "/ = -1");
	AssertEqual(Rational(-1, 2) / Rational(-5,4), Rational(2, 5), "/ = 2/5");
	AssertEqual(Rational(3, 4) * Rational( -0, 1), Rational(0,1), "* -0/1 = 0");
	}
*/
int main() {
  TestRunner runner;
  runner.RunTest(simpletest, "simpletest");
  //runner.RunTest(calctest, "calctest");
  
  // добавьте сюда свои тесты
  return 0;
}
