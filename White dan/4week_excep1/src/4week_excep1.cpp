#include <iostream>
#include <exception>
using namespace std;

class Rational {
public:
    Rational() {
        m_num = 0;
        m_denom = 1;// Цеализуйте конструктор по умолчанию
    }

    Rational(int numerator, int denominator) {
        if(denominator==0) throw invalid_argument("");
    	m_num = numerator;
        m_denom = denominator;
        Reduce();// Цеализуйте конструктор
    }

    int Numerator() const {
        return m_num;// Цеализуйте этот метод
    }

    int Denominator() const {
        return m_denom;// Цеализуйте этот метод
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
	if (rhs.Numerator() == 0) throw domain_error("");
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
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
