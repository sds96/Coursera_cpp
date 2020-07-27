#ifndef BOOKING_H_
#define BOOKING_H_

#include <utility>

namespace RAII{

template <typename Provider>
class Booking{
private:
	Provider* prov;
	int id;
public:
	Booking(Provider* p, int& i)
	: prov(p), id(i)
	{}

	Booking(const Booking&) = delete;
	Booking(Booking&& other){
		prov = std::move(other.prov);
		other.prov = nullptr;
		id = std::move(other.id);
	};

	Booking& operator=(const Booking&) = delete;
	Booking& operator=(Booking&& other){
		prov = std::move(other.prov);
		other.prov = nullptr;
		id = std::move(other.id);
		return *this;
	};

	~Booking(){
		if(prov)
			prov->CancelOrComplete(*this);
	}
};

}



#endif /* BOOKING_H_ */
