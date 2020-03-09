#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() {
        m_num = 0;
        m_denom = 1;// Реализуйте конструктор по умолчанию
    }

    Rational(int numerator, int denominator) {
        m_num = numerator;
        m_denom = denominator;
        Reduce();// Реализуйте конструктор
    }

    int Numerator() const {
        return m_num;// Реализуйте этот метод
    }

    int Denominator() const {
        return m_denom;// Реализуйте этот метод
    }

private:
    int m_num;
    int m_denom;

    void Reduce (){
    	if(m_denom < 0) {
    		m_num*=-1;
    		m_denom *=-1;
    	}
    	if (m_num == 0) {
    		m_denom = 1;
    		return;
    	}
    	for (int i = abs(m_num); i > 0; i--) {
    	        if (m_num % i == 0 && m_denom % i == 0) {
    	            m_num /=i;
    	            m_denom /=i;
    	            break;
    	        }
    	    }

    }
};

Rational operator+(const Rational& lhs, const Rational& rhs){
	if (lhs.Denominator() == rhs.Denominator())
		return Rational(lhs.Numerator()+rhs.Numerator(), lhs.Denominator());
	else
		return Rational(lhs.Numerator()*rhs.Denominator() + rhs.Numerator()*lhs.Denominator(),
						lhs.Denominator()*rhs.Denominator());
}

bool operator == (const Rational& lhs, const Rational& rhs){
   	if (lhs.Denominator() == rhs.Denominator())
   		return lhs.Numerator() == rhs.Numerator();
   	else return false;
   }

Rational operator-(const Rational& lhs, const Rational& rhs){
	if (lhs.Denominator() == rhs.Denominator())
		return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
	else return Rational(lhs.Numerator()*rhs.Denominator() - rhs.Numerator()*lhs.Denominator(),
			lhs.Denominator()*rhs.Denominator());;
}

Rational operator*(const Rational& lhs, const Rational& rhs){
	return Rational (lhs.Numerator() * rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs){
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

ostream& operator<<(ostream& stream, const Rational& rhs){
	return stream << rhs.Numerator() << "/" << rhs.Denominator();
}

istream& operator>>(istream& stream, Rational& rhs){
	int a=rhs.Numerator(),b = rhs.Denominator();
	stream >> a;
	stream.ignore(1);
	stream >> b;
	rhs = Rational(a,b);
	return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs){
	if (lhs.Denominator() == rhs.Denominator())
		return lhs.Numerator() < rhs.Numerator();
	else return lhs.Numerator()*rhs.Denominator() < rhs.Numerator()*lhs.Denominator();
}


int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
