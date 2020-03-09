#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ReversibleString{
	private:
	string m_str;
	
	public:
	
	ReversibleString(){};
	ReversibleString(const string &new_str){
		m_str = new_str;
	};
	void Reverse(){
		reverse(m_str.begin(), m_str.end());
	};
	
	string ToString() const{
		return m_str;
	};
	
};