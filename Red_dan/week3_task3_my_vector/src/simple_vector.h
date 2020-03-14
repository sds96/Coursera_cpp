#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(): data(nullptr), size_(0), cap_(0)
  {};

  explicit SimpleVector(size_t size){
	  size_ = size;
	  cap_ = size;
	  data = new T[size_];
  };
  ~SimpleVector(){
	  delete[] data;
  };

  T& operator[](size_t index){
	  return data[index];
  };

  T* begin() { return data;};
  T* end() { return data+size_;};
  const T* begin() const { return data;};
  const T* end() const { return data+size_;};
  size_t Size() const { return size_;};
  size_t Capacity() const {	return cap_;};

  void PushBack(const T& value){
	  if(size_ == cap_){
		  if (size_==0)
			  cap_++;
		   else
			  cap_*=2;
		T* temp = new T[cap_];
		for(size_t i = 0; i< size_;++i){
			temp[i]= data[i];
		}
		delete[] data;
		data = temp;

	  }
	  data[size_] = value;
	  ++size_;
  };

private:
  T* data;// Добавьте поля для хранения данных вектора
  size_t size_;
  size_t cap_;
};
