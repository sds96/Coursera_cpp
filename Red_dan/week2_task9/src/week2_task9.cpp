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
/*
class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    // ѕо умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // ѕростой способ сделать это Ч умножить его на 1.0.
    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:
  // —татическое поле не принадлежит какому-то конкретному
  // объекту класса. ѕо сути это глобальна€ переменна€,
  // в данном случае константна€.
  // Ѕудь она публичной, к ней можно было бы обратитьс€ снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
  vector<int> user_positions_; // позиции в векторе sorted_users_

  int GetUserCount() const {
    return sorted_users_.size();
  }
  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};
*/

int main() {
  // ƒл€ ускорени€ чтени€ данных отключаетс€ синхронизаци€
  // cin и cout с stdio,
  // а также выполн€етс€ отв€зка cin от cout
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
