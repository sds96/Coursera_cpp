#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  unique_ptr<Worker> _next;
  void PassOn(unique_ptr<Email> email) const{
	  if(_next)
		  _next->Process(move(email));
  };

public:
  void SetNext(unique_ptr<Worker> next) {
	  if(!_next)
		  _next = move(next);
	  else
		  _next->SetNext(move(next));
  };
};


class Reader : public Worker {
public:
  Reader(istream& in){
		Email _email;
	    while (getline(in,_email.from) && getline(in,_email.to) && getline(in,_email.body)) {
	    	emails.emplace_back(make_unique<Email>(move(_email)));
	    }
  }

	void Run() final{
		for(auto& e : emails)
			Process(move(e));
    }

	void Process(unique_ptr<Email> email) override{
		PassOn(move(email));
	}
private:
	vector<unique_ptr<Email>> emails;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;
  Function f;
public:
	// реализуйте класс
	Filter(Function p): f(move(p)){
	}
	void Process(unique_ptr<Email> email) override{
		if (f(*email)){
			PassOn(move(email));
		}
	}
};


class Copier : public Worker {
public:
    // реализуйте класс
	Copier(const string& adress): copy_to(adress){
	}
	void Process(unique_ptr<Email> email) override{
		unique_ptr<Email> new_email = nullptr;

		if(email->to != copy_to){
			new_email = move(make_unique<Email>(Email{email->from, copy_to, email->body}));
		}
		PassOn(move(email));

		if(new_email)
			PassOn(move(new_email));

	}
private:
	string copy_to;
};


class Sender : public Worker {
public:
	// реализуйте класс
	ostream& osss;
	Sender(ostream& os): osss(os)	{

	}
	void Process(unique_ptr<Email> email) override{
		osss << email->from << "\n" <<
				email->to << "\n" <<
				email->body << "\n";
		PassOn(move(email));
	}
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in){
	  pipeline = make_unique<Reader>(in);
  };

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter){
	  pipeline->SetNext(make_unique<Filter>(move(filter)));
	  return *this;
  };

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient){
	  pipeline->SetNext(make_unique<Copier>(recipient));
	  return *this;
  };

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out){
	  pipeline->SetNext(make_unique<Sender>(out));
	  return *this;
  };

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build(){
	  return move(pipeline);
  };

private:
  unique_ptr<Worker> pipeline;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
