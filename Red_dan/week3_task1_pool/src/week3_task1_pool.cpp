#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
	  if(deallocated.empty()){
		  T* new_obj = new T;
		  allocated.insert(new_obj);
		  return new_obj;
	  }
	  else{
		  auto curr = deallocated.front();
		  allocated.insert(curr);
		  deallocated.pop();
		  return curr;
	  }
  };
  T* TryAllocate(){
	  if(deallocated.empty()){
		  return nullptr;
	  }
	  else{
		  auto curr = deallocated.front();
		  allocated.insert(curr);
		  deallocated.pop();
		  return curr;
	  }
  };

  void Deallocate(T* object){
	  if(allocated.count(object) < 1){
		  throw invalid_argument("");
	  } else{
		  deallocated.push(object);
		  allocated.erase(object);
	  }
  };

  ~ObjectPool(){
	  for(auto& el: allocated){
		  delete el;
	  }
	  allocated.clear();
	  while(!deallocated.empty()){
		  delete deallocated.front();
		  deallocated.pop();
	  }
  };

private:
  set<T*> allocated;
  queue<T*> deallocated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
