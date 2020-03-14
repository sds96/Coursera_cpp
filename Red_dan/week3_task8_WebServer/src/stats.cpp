#include "stats.h"
#include <algorithm>

using namespace std;

const array<string, 5> Stats::MethodNames = {"GET",
                                             "PUT",
                                             "POST",
                                             "DELETE",
                                             "UNKNOWN"};
const array<string, 6> Stats::UriNames = {"/",
                                          "/order",
                                          "/product",
                                          "/basket",
                                          "/help",
                                          "unknown"};

Stats::Stats(){
    for (const string_view method_name : MethodNames)
    {
        Methods[method_name] = 0;
    }
    for (const string_view uri_name : UriNames)
    {
        Uri[uri_name] = 0;
    }
};

void Stats::AddMethod(string_view method){
	  if (find(Stats::MethodNames.begin(), Stats::MethodNames.end(), method) != Stats::MethodNames.end())
		  Methods[method]++;
	  else
		  Methods["UNKNOWN"]++;
};
void Stats::AddUri(string_view uri){
	  if (find(Stats::UriNames.begin(), Stats::UriNames.end(), uri) != Stats::UriNames.end())
		  Uri[uri]++;
	  else
		  Uri["unknown"]++;
};
const map<string_view, int>& Stats::GetMethodStats() const{
	  return Methods;
};
const map<string_view, int>& Stats::GetUriStats() const{
	  return Uri;
};

HttpRequest ParseRequest(string_view line){
	HttpRequest ret;
	line.remove_prefix(line.find_first_not_of(' '));
	auto pos = line.find(' ');
	ret.method = line.substr(0, pos);
	if (pos == line.npos) {
		ret.uri = "unknown";
		return ret;
	}
	line.remove_prefix(pos+1);
	pos = line.find(' ');
	ret.uri = line.substr(0, pos);
	if (pos != line.npos)
		ret.protocol = line.substr(pos + 1);
	return ret;
};
