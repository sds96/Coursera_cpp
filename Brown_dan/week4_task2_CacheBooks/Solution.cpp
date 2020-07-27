#include "Common.h"
#include <list>
#include <unordered_map>
#include <algorithm>
#include <future>

using namespace std;

//using BookPtr = std::shared_ptr<const IBook>;

class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ) :unpacker(books_unpacker), sets(settings), mem_used(0) {
    // реализуйте метод
  }

  BookPtr GetBook(const string& book_name) override {
    // Если книга есть в кеше - отдать из кеша, если нет - загрузить
	  BookPtr ret;
	  m.lock();
	  if(BookInCache(book_name)){
		  ret = name_to_ptr[book_name];
		  UpBook(ret);
	  } else{
		  ret = unpacker->UnpackBook(book_name);
	  	  PutInCache(ret);
	  }
	  m.unlock();
	  return ret;
  }

  bool BookInCache(const string& book_name) const {
	  if(name_to_ptr.count(book_name))
		  return true;
	  else
		  return false;
  }

  void UpBook(BookPtr ptr){
	  auto it = find(cache.begin(), cache.end(), ptr);
	  cache.erase(it);
	  cache.push_front(ptr);
  }

  void PutInCache(BookPtr ptr){
	  if(ptr->GetContent().size() > sets.max_memory)
		  return;
	  if(mem_used+ptr->GetContent().size() <= sets.max_memory){
		  name_to_ptr[ptr->GetName()] = ptr;
		  cache.push_front(ptr);
		  mem_used+=ptr->GetContent().size();
	  } else {
		  while (mem_used+ptr->GetContent().size() > sets.max_memory){
			  mem_used -= cache.back()->GetContent().size();
			  name_to_ptr.erase(cache.back()->GetName());
			  cache.pop_back();
		  }
		  name_to_ptr[ptr->GetName()] = ptr;
		  cache.push_front(ptr);
		  mem_used+=ptr->GetContent().size();
	  }
  }
private:
  unordered_map<string, BookPtr> name_to_ptr;
  list<BookPtr> cache;
  shared_ptr<IBooksUnpacker> unpacker;
  Settings sets;
  size_t mem_used;
  mutex m;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  return make_unique<LruCache>(books_unpacker, settings);
}
