// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class FuncParts{
private:
    char operation;
    double m_value;
public: 
    FuncParts(char op, double val){
        operation = op;
        m_value = val;
        };
    double Apply (double &val) const{
        if (operation == '+')
            return val + m_value;
        else 
            return val - m_value;
        };
    void Invert(){
        if (operation == '+')
            operation = '-';
        else 
            operation = '+';
        };
    };

class Function {
public:
    void AddPart(const char c, double value){
        parts.push_back({c, value});
        };
    double Apply (double val) const{
        for (const auto& i: parts)
            val = i.Apply(val);
        return val;
        };
    void Invert(){
        for (auto& i: parts)
            i.Invert();
		reverse(begin(parts), end(parts));
        };
    
private:
    vector<FuncParts> parts;
    };

	// ========================================= test ==================
/*	
struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};
	
Function MakeWeightFunction(const Params& params,
                            const Image& image) {
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl;
  cout << ComputeQualityByWeight(params, image, 46) << endl;
  return 0;
}
*/