// Example program
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>

using namespace std;
template <typename First, typename Second>  // pair operator
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2);
template <typename First, typename Second>  // for pair
pair<First, Second> Sqr (const pair<First,Second>& p);
template <typename Key, typename Value>   // for map
map<Key, Value> Sqr (const map<Key, Value>& m);
template <typename T>       // for vector
vector<T> Sqr (const vector<T>& v);
template <typename T>       // for simple
T Sqr(T x);

template <typename T>
T Sqr(T x){
    return x*x;
    }

template <typename First, typename Second> 
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2){
    return make_pair(p1.first*p2.first, p1.second*p2.second);
    };

template <typename First, typename Second>  // for pair
pair<First, Second> Sqr (const pair<First,Second>& p){
    pair<First, Second> out;
    out = p*p;
    return out;
    };

template <typename Key, typename Value>   // for map
map<Key, Value> Sqr (const map<Key, Value>& m){
    map<Key, Value> out;
    for (const auto& el:m){
        out[el.first] = Sqr(el.second);
        }
    return out;
    };

template <typename T>       // for vector
vector<T> Sqr (const vector<T>& v){       
    vector<T> out;
    for (auto el: v){
        out.push_back(Sqr(el));
        }
    return out;
    };

int main()
{
vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
  cout << ' ' << x;
}
cout << endl;

map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
vector<map<int, vector<double>>> it = { { {2, { 3, 4,5,6.8 }}}, { {5, {6, 7,0.01}} } }; // MEGA TEST
Sqr(it);
}
