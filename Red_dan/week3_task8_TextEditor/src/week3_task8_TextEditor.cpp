#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <iostream>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // –еализуйте конструктор по умолчанию и объ€вленные методы
  Editor(){
	  pointer = text.begin();
  };
  void Left(){
	  if (pointer != text.begin()){
		  pointer = prev(pointer);
	  }
  };
  void Right(){
	  if(pointer != text.end()){
		  pointer = next(pointer);
	  }
  };
  void Insert(char token){
	  text.insert(pointer, token);
  };
  void Cut(size_t tokens = 1){
	  size_t dist = distance(pointer, text.end());
		if (dist > tokens) {
		  auto it = next(pointer, tokens);
		  buff = vector<char>(pointer, it);
		  text.erase(pointer, it);
		  pointer = it;
		} else {
		  buff = vector<char>(pointer, text.end());
		  text.erase(pointer, text.end());
		  pointer = text.end();
		}
  };
  void Copy(size_t tokens = 1){
      size_t dist = distance(pointer, text.end());
      if (dist > tokens) {
        buff = vector<char>(pointer, next(pointer, tokens));
      } else {
        buff = vector<char>(pointer, text.end());
      }
  };
  void Paste(){
	  text.insert(pointer, buff.begin(),buff.end());
  };
  string GetText() const{
	  string ret;
	  for(const auto& el: text)
		  ret+=el;
	  return ret;
  };
 private:
  list<char> text;
  vector<char> buff;
  list<char>::iterator pointer;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

void TestCut()
{
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//5
	editor.Cut(5);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bcde");
	editor.Right();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
	Editor editor;
	//1
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	ASSERT_EQUAL(editor.GetText(), "a");
	//2
	editor.Copy(1);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");//between a
    //3
	editor.Copy(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcdea");
};

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, TestCopy);
  RUN_TEST(tr, TestCut);
  return 0;
}
