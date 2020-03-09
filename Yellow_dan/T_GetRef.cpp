// Example program
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

template <typename K, typename V>
V& GetRefStrict(map<K, V>& m, K key);

using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& m, K key){
    if(m.count(key)==0) throw runtime_error("");
    return m.at(key);
    }; 

/*
int main()
{
map<int, string> m = {{0, "value"}};
string& item = GetRefStrict(m, 0);
item = "newvalue";
cout << m[0] << endl; // выведет newvalue
}
*/