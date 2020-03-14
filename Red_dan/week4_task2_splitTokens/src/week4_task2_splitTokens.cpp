#include "test_runner.h"

#include <vector>
#include <utility>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  // Напишите реализацию функции, не копируя объекты типа Token
	vector<Sentence<Token>> ret;
	Sentence<Token> buff;
	auto it = tokens.begin();
	while(it!=tokens.end()){
		auto it_next = it+1;
		buff.push_back(move(*it));
		if(it_next == tokens.end()){
			ret.push_back(move(buff));
			buff.clear();
		} else if(buff.back().IsEndSentencePunctuation() && !(it_next->IsEndSentencePunctuation())){
			ret.push_back(move(buff));
			buff.clear();
		}

		it = it_next;
	}

	return ret;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};


ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}
/*
void TestUnCopy(){
	vector<NoncopyableInt> vec;
	vec.push_back({1});
	vec.push_back({2});
	vec.push_back({3,true});

	vector<NoncopyableInt> vec_m;
		vec.push_back({1});
		vec.push_back({2});
		vec.push_back({3,true});

	vector<Sentence<NoncopyableInt>> vec2(1);
		vec2[0].push_back({1});
		vec2[0].push_back({2});
		vec2[0].push_back({3,true});
	vector<Sentence<NoncopyableInt>> vec3;
	vec3.push_back(move(vec_m));
	ASSERT_EQUAL(SplitIntoSentences(vec), vec3);
}
*/
int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  //RUN_TEST(tr, TestUnCopy);
  return 0;
}
