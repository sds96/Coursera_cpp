#pragma once

#include <cstdlib>
#include <algorithm>

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

  SimpleVector<T>(const SimpleVector<T>& rhs)
		  : data(new T[rhs.cap_]),size_(rhs.size_), cap_(rhs.cap_)
  {
	  std::copy(rhs.begin(), rhs.end(), this->begin());
  }
  SimpleVector<T>& operator=(const SimpleVector<T> rhs){
	  delete[] this->data;
	  this->cap_ = rhs.cap_;
	  this->size_ = rhs.size_;
	  this->data = new T[this->cap_];
	  std::copy(rhs.begin(), rhs.end(), this->begin());
	  return *this;
  }

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
