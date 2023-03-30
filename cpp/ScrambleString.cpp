#include <functional>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  bool isScramble(string s1, string s2) {
    unordered_map<int, bool> memo;
    function<bool(const int, const int, const int)> dp;
    function<bool(const int, const int, const int, const int)> trySlice;

    trySlice = [&](const int s1_begin, const int s2_begin, const int length,
                   const int leftSliceSize) -> bool {
      if (leftSliceSize == length) {
        return false;
      }

      return (dp(s1_begin, s2_begin, leftSliceSize) &&
              dp(s1_begin + leftSliceSize, s2_begin + leftSliceSize,
                 length - leftSliceSize)) ||
             (dp(s1_begin, s2_begin + length - leftSliceSize, leftSliceSize) &&
              dp(s1_begin + leftSliceSize, s2_begin, length - leftSliceSize)) ||
             trySlice(s1_begin, s2_begin, length, leftSliceSize + 1);
    };

    dp = [&](const int s1_begin, const int s2_begin, const int length) -> bool {
      if (length == 1) {
        return s1[s1_begin] == s2[s2_begin];
      }

      const int key = (s1_begin << 10) | (s2_begin << 5) | length;
      if (auto iter{memo.find(key)}; iter != memo.end()) {
        return iter->second;
      }

      return memo[key] = trySlice(s1_begin, s2_begin, length, 1);
    };

    return dp(0, 0, static_cast<int>(s1.length()));
  }
};