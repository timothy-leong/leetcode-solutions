#include <string>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  bool isScramble(string s1, string s2) {
    unordered_map<int, bool> memo;
    return dp(s1, s2, 0, 0, s1.length(), memo);
  }

  bool dp(string& s1, string& s2, const int s1_begin, const int s2_begin,
          const int length, unordered_map<int, bool>& memo) {
    if (length == 1) {
      return s1[s1_begin] == s2[s2_begin];
    }

    const int key = (s1_begin << 10) | (s2_begin << 5) | length;
    if (auto iter{memo.find(key)}; iter != memo.end()) {
      return iter->second;
    }

    bool result{};
    for (int left_cut = 1; left_cut < length && !result; ++left_cut) {
      result =
          (dp(s1, s2, s1_begin, s2_begin, left_cut, memo) &&
           dp(s1, s2, s1_begin + left_cut, s2_begin + left_cut,
              length - left_cut, memo)) ||
          (dp(s1, s2, s1_begin, s2_begin + length - left_cut, left_cut, memo) &&
           dp(s1, s2, s1_begin + left_cut, s2_begin, length - left_cut, memo));
    }

    return memo[key] = result;
  }
};