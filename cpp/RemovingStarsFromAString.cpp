#include <string>
using namespace std;

class Solution {
 public:
  string removeStars(string s) {
    string result;
    result.reserve(s.length());
    int asterisks{};
    for (auto iter = s.rbegin(); iter != s.rend(); ++iter) {
      if (*iter == '*') {
        ++asterisks;
      } else if (asterisks > 0) {
        --asterisks;
      } else {
        result.push_back(*iter);
      }
    }

    reverse(result.begin(), result.end());
    return result;
  }
};