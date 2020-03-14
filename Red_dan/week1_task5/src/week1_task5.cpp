//============================================================================
// Name        : week1_task5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <exception>
//#include "test_runner.h"
using namespace std;

template<class T>
class Deque{
public:
	vector<T> front;
	vector<T> back;

	bool Empty() const {
		if(front.empty() && back.empty())
			return true;
		else
			return false;
	}
	size_t Size() const{
		return front.size()+back.size();
	}
	T& At(size_t index){
		if(index < 0 || index >= front.size()+back.size())
			throw out_of_range("");
		else
			return (*this)[index];
	}

	const T& At(size_t index) const{
		if(index < 0 || index >= front.size()+back.size())
			throw out_of_range("");
		else
			return (*this)[index];
	}

	T& operator[](size_t index){
		if (index < front.size())
			return front[front.size()-index-1];
		else
			return back[index-front.size()];
	}
	const T& operator[](size_t index) const{
		if (index < front.size())
			return front[front.size()-index-1];
		else
			return back[index-front.size()];
	}

	T& Front(){
		if(!front.empty())
			return *(--front.end());
		else
			return back[0];
	}
	const T& Front() const {
		if(!front.empty())
			return *(--front.end());
		else
			return back[0];
	}

	T& Back(){
		if(!back.empty())
			return *(--back.end());
		else
			return front[0];
	}
	const T& Back() const {
		if(!back.empty())
			return *(--back.end());
		else
			return front[0];
	}

	void PushFront(T el){
		front.push_back(el);
	}
	void PushBack(T el){
		back.push_back(el);
	}

};
/*
void TestEmpty() {
  Deque<int> dq;
  ASSERT(dq.Empty());
}

void TestPush() {
  Deque<int> dq;
  dq.PushBack(2);
  dq.PushFront(1);
  ASSERT(!dq.Empty());
}

void TestSize() {
  Deque<int> dq;
  dq.PushBack(2);
  dq.PushFront(1);
  ASSERT_EQUAL(dq.Size(), 2u);
}

void TestFront() {
  Deque<int> dq;
  dq.PushFront(1);
  ASSERT_EQUAL(dq.Front(), 1);
  dq.PushBack(2);
  ASSERT_EQUAL(dq.Front(),1);

  dq.PushFront(0);
  ASSERT_EQUAL(dq.Front(), 0);

  Deque<int> dq2;
  dq2.PushBack(1);
  ASSERT_EQUAL(dq2.Front(),1);
}

void TestBack() {
  Deque<int> dq;
  dq.PushBack(1);
  ASSERT_EQUAL(dq.Back(), 1);
  dq.PushFront(2);
  ASSERT_EQUAL(dq.Back(), 1);

  dq.Back() = 0;
  ASSERT_EQUAL(dq.Back(), 0);
}

void TestOperator() {
  // front и back имеют элементы
  Deque<int> dq_of_int;
  dq_of_int.PushFront(1);
  dq_of_int.PushFront(2);
  dq_of_int.PushFront(3);
  dq_of_int.PushBack(4);
  dq_of_int.PushBack(5);
  ASSERT_EQUAL(dq_of_int[0], 3);
  ASSERT_EQUAL(dq_of_int[1], 2);
  ASSERT_EQUAL(dq_of_int[2], 1);
  ASSERT_EQUAL(dq_of_int[3], 4);
  ASSERT_EQUAL(dq_of_int[4], 5);

  // front имеет элементы, back Ц пуст
  Deque<double> dq_of_db;
  dq_of_db.PushFront(1.5);
  dq_of_db.PushFront(2.5);
  dq_of_db.PushFront(3.5);
  ASSERT_EQUAL(dq_of_db[0], 3.5);
  ASSERT_EQUAL(dq_of_db[1], 2.5);
  ASSERT_EQUAL(dq_of_db[2], 1.5);

  // back имеет элементы, front Ц пуст
  Deque<char> dq_of_ch;
  dq_of_ch.PushBack('a');
  dq_of_ch.PushBack('b');
  ASSERT_EQUAL(dq_of_ch[0], 'a');
}

void TestAt() {
  // front и back имеют элементы
  Deque<int> dq_of_int;
  dq_of_int.PushFront(1);
  dq_of_int.PushFront(2);
  dq_of_int.PushFront(3);
  dq_of_int.PushBack(4);
  dq_of_int.PushBack(5);
  ASSERT_EQUAL(dq_of_int.At(0), 3);
  ASSERT_EQUAL(dq_of_int.At(1), 2);
  ASSERT_EQUAL(dq_of_int.At(2), 1);
  ASSERT_EQUAL(dq_of_int.At(3), 4);
  ASSERT_EQUAL(dq_of_int.At(4), 5);

  // front имеет элементы, back Ц пуст
  Deque<double> dq_of_db;
  dq_of_db.PushFront(1.5);
  dq_of_db.PushFront(2.5);
  dq_of_db.PushFront(3.5);
  ASSERT_EQUAL(dq_of_db.At(0), 3.5);
  ASSERT_EQUAL(dq_of_db.At(1), 2.5);
  ASSERT_EQUAL(dq_of_db.At(2), 1.5);

  try {
    dq_of_db.At(3);
  } catch (const out_of_range& ex) {
    bool exception_caught = true;
    ASSERT(exception_caught);
  }

  // back имеет элементы, front Ц пуст
  Deque<char> dq_of_ch;
  dq_of_ch.PushBack('a');
  dq_of_ch.PushBack('b');
  ASSERT_EQUAL(dq_of_ch.At(0), 'a');
}

void FinalTest() {
    Deque<string> dq;
    dq.PushBack("A");
    ASSERT_EQUAL(dq.Front(), "A");
    ASSERT_EQUAL(dq.Back(), "A");
    dq.PushBack("B");
    dq.PushBack("C");
    dq.PushBack("D");
    ASSERT_EQUAL(dq.Front(), "A");
    ASSERT_EQUAL(dq.Back(), "D");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestPush);
  RUN_TEST(tr, TestSize);
  RUN_TEST(tr, TestFront);
  RUN_TEST(tr, TestBack);
  RUN_TEST(tr, TestOperator);
  RUN_TEST(tr, TestAt);
  RUN_TEST(tr, FinalTest);
  return 0;
}
*/
