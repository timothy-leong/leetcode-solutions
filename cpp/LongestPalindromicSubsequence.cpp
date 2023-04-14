#include <functional>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
 public:
  // clang-format off
    /**
     * Let longestPalindrome(i, j) refer to the 
     * longest palindrome attainable in s[i:j] (j inclusive).
     * We want longestPalindrome(0, s.length() - 1).
     * 
     * longestPalindrome(i, j) = 
     * | 0                                                                if i > j
     * | 1 + (i < j ? 1 : 0) + longestPalindrome(i + 1, j - 1)            if s[i] == s[j]
     * | max(longestPalindrome(i + 1, j), longestPalindrome(i, j - 1))    otherwise
     */
  // clang-format on
  int longestPalindromeSubseq(string s) {
    unordered_map<int, int> memo;

    function<int(const int, const int)> dp;
    dp = [&](const int i, const int j) {
      if (i > j) {
        return 0;
      }

      const int key = (i << 10) | j;
      if (auto iter{memo.find(key)}; iter != memo.end()) {
        return iter->second;
      }

      return memo[key] = s[i] == s[j] ? 1 + (i < j ? 1 : 0) + dp(i + 1, j - 1)
                                      : max(dp(i + 1, j), dp(i, j - 1));
    };

    return dp(0, s.length() - 1);
  }
};