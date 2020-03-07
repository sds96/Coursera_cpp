#include <iostream>
#include <exception>
#include <system_error>
#include <string>
using namespace std;


class TimeServer {
public:
  string GetCurrentTime()
  {
      try {
          string tm = AskTimeServer();
          LastFetchedTime = tm;
      } catch(const system_error&) {}
      return LastFetchedTime;
  }
private:
  string LastFetchedTime = "00:00:00";
};


int main() {
    // ћен€€ реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
