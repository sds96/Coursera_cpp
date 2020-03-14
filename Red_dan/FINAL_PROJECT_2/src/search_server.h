#pragma once

#include <mutex>
#include <future>
#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <string_view>
using namespace std;

template<size_t N, typename Container>
inline array<pair<size_t, typename Container::value_type>, N> GetRelevantElements(const Container& c) {

    using T = typename Container::value_type;

    array<pair<size_t, T>, N> result;
    result.fill({SIZE_MAX,T{}});

    size_t curr_index;
    pair<size_t, T> value;
    for (size_t i = 0; i < c.size(); ++i)
    {
        if (c[i] <= result[N-1].second) continue;
        curr_index = i > N-1 ? N-1 : i;
        value = {i, c[i]};
        while (curr_index > 0 && value.second > result[curr_index - 1].second) {
            result[curr_index] = result[curr_index - 1];
            --curr_index;
        }
        result[curr_index] = value;
    }

    return result;
}

class InvertedIndex {
public:
  void Add(string&& document);
  const vector<pair<size_t,size_t>>& Lookup(string_view word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

  const size_t GetNumDocs() const{
	  return docs.size();
  }

private:
  map<string_view, vector<pair<size_t, size_t>>> index_map;
  deque<string> docs;
  vector<pair<size_t,size_t>> empty_lookup;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
  mutex m;
  vector<future<void>> futures;
  bool init = false;
};
