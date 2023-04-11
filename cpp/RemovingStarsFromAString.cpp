#include <string>
using namespace std;

class Solution {
 public:
  string removeStars(string s) {
    int cursor{};
    for (int i{}; i < s.length(); ++i) {
      if (s[i] != '*') {
        s[cursor++] = s[i];
      } else {
        --cursor;
      }
    }
    s.resize(cursor);
    return s;
  }
};