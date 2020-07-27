#include "test_runner.h"

#include <functional>
#include <string>
#include <optional>
#include <map>

using namespace std;

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()> init){
	  f = init;
  };

  bool HasValue() const{
	  return lazy.has_value();
  };
  const T& Get() const{
	  if (!HasValue()) {
		  lazy = optional<T>(f());
	  }
	  return lazy.value();
  };

private:
  mutable optional<T> lazy;
  std::function<T()> f;
};

void UseExample() {
  const string big_string = "Giant amounts of memory";

  LazyValue<string> lazy_string([&big_string] { return big_string; });

  ASSERT(!lazy_string.HasValue());
  ASSERT_EQUAL(lazy_string.Get(), big_string);
  ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
  bool called = false;

  {
    LazyValue<int> lazy_int([&called] {
      called = true;
      return 0;
    });
  }
  ASSERT(!called);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, UseExample);
  RUN_TEST(tr, TestInitializerIsntCalled);
  return 0;
}
