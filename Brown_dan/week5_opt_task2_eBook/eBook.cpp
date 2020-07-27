#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : page_of_user(MAX_USER_COUNT + 1, 0),
        users_less_than_page(MAX_PAGES + 1),
		users_count(0) {}

  void Read(int user_id, int page_count) {
    if (page_of_user[user_id] == 0) {
      page_of_user[user_id] = page_count;
      users_count++;
      for(int i = page_count+1; i <= MAX_PAGES; ++i)
    	  users_less_than_page[i]++;
    }
    else{
    	for (int i = page_of_user[user_id]+1; i <= page_count; ++i)
    		users_less_than_page[i]--;
    	page_of_user[user_id] = page_count;
    }

  }

  double Cheer(int user_id) const {
    if (page_of_user[user_id] == 0) {
      return 0;
    }
    if (users_count == 1) {
      return 1;
    }
    return users_less_than_page[page_of_user[user_id]] * 1.0 / (users_count - 1);
  }

private:
  static const int MAX_USER_COUNT = 100000;
  static const int MAX_PAGES = 1000;

  vector<int> page_of_user;
  vector<int> users_less_than_page;
  int users_count;
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
