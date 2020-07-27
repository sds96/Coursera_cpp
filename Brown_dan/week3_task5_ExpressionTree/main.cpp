#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}


class Num: public Expression{
private:
	int num;
public:
	virtual ~Num() = default;

	Num(int value): num(value){};

	int Evaluate() const override {
		return num;
	};

	std::string ToString() const override {
		return to_string(num);
	};
};

class Summa: public Expression{
private:
	ExpressionPtr _left;
	ExpressionPtr _right;
public:
	Summa(ExpressionPtr left, ExpressionPtr right):
		_left(move(left)), _right(move(right))
	{};

	int Evaluate() const override {
		return _left->Evaluate() + _right->Evaluate();
	}

	std::string ToString() const override {
		string ret = "(" + _left->ToString() + ")+(" + _right->ToString() + ")";
		return ret;
	};
};

class Mult: public Expression{
private:
	ExpressionPtr _left;
	ExpressionPtr _right;
public:
	Mult(ExpressionPtr left, ExpressionPtr right):
		_left(move(left)), _right(move(right))
	{};

	int Evaluate() const override {
		return _left->Evaluate() * _right->Evaluate();
	}

	std::string ToString() const override {
		string ret = "(" + _left->ToString() + ")*(" + _right->ToString() + ")";
		return ret;
	};
};

ExpressionPtr Value(int value){
	return make_unique<Num>(value);
};

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
	return make_unique<Summa>(move(left), move(right));
};

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
	return make_unique<Mult>(move(left), move(right));
};

void Simple() {
  ExpressionPtr e1 = Value(2);
  ASSERT_EQUAL(Print(e1.get()),"2 = 2");

  ExpressionPtr e2 = Value(3);
  ASSERT_EQUAL(e2->Evaluate(), 3);
}

void Summing(){
	ExpressionPtr e1 = Sum(Value(1), Value(1));
	ASSERT_EQUAL(Print(e1.get()), "(1)+(1) = 2");

	ExpressionPtr e2 = Sum(Value(1), Value(1));
	ASSERT_EQUAL(e2->Evaluate(), 2);

	e1 = Sum(Sum(Value(1), Value(2)), Sum(Value(3), Value(4)));
	ASSERT_EQUAL(Print(e1.get()), "((1)+(2))+((3)+(4)) = 10");
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Simple);
  RUN_TEST(tr, Summing);
  RUN_TEST(tr, Test);
  return 0;
}
