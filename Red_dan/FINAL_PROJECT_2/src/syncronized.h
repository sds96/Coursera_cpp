#ifndef SYNCRONIZED_H_
#define SYNCRONIZED_H_

#include <mutex>
#include <future>
#include <utility>

template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T()): value(std::move(initial))
  {
  };

  struct Access {
    T& ref_to_value;
    std::lock_guard<std::mutex> guard;
  };

  Access GetAccess(){
	  return {value, std::lock_guard<std::mutex>(m)};
  };

private:
  T value;
  std::mutex m;
};



#endif /* SYNCRONIZED_H_ */