#include <string>
using namespace std;

class Solution {
 public:
  string mergeAlternately(string word1, string word2) {
    string result;
    result.reserve(word1.size() + word2.size());
    merge(word1, word2, result);
    return result;
  }

  void merge(string_view first, string_view second, string& result) {
    if (first.empty()) {
      result += second;
    } else if (second.empty()) {
      result += first;
    } else {
      result.push_back(first[0]);
      merge(second, first.substr(1), result);
    }
  }
};