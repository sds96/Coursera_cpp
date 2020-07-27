#ifndef GEO_H_
#define GEO_H_

#include <cmath>
#include <iostream>
#include <vector>

static const double PI =  3.1415926535;
static const int EARTH_RADIUS = 6371000; // in meters

class Point{
private:
	friend std::istream& operator>>(std::istream& is, Point& point);
	friend std::ostream& operator<<(std::ostream& os, const Point& point);

	double latitude;
	double longitude;
public:
	Point ()
		: latitude(0.0), longitude (0.0)
	{}
	Point (double la, double lo)
		: latitude(la), longitude(lo)
	{};

	double GetLatitude() const;
	double GetLongitude() const;
};

double ComputeDistance (Point lhs, Point rhs);

std::vector<std::string> split(const std::string& s, const std::string& separator);
std::vector<std::string> split(const std::string& s, const char separator);

#endif
