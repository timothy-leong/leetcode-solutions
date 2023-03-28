#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  bool isMatch(string s, string p) {
    // clang-format off
        /**
         * Let isMatch(i, j) refer to whether s[i:] can be matched by p[j:].
         * Let char_match[i] = s[i] == p[j] || p[j] == '.',
         * and let wildcard = j + 1 < p.length() && p[j + 1] == '*'
         * Then isMatch(i, j) =
         * | true                             if i == s.length() && j == p.length()       // Vacuously true
         * | false                            if j == p.length()                          // An empty pattern cannot match a non-empty string 
         * | wildcard && isMatch(i, j + 2)    if i == s.length()                          // The only pattern that matches an empty string 
         *                                                                                   is one comprising only asterisks 
         * | isMatch(i + 1, j + 1)            if char_match && !wildcard                  // 1 letter in s matches 1 letter in p 
         * | isMatch(i, j + 2)                if !char_match && wildcard                  // e.g. xbc matching with a*xbc 
         * | dp(i, j + 2) || dp(i + 1, j) || dp(i + 1, j + 2) if char_match && wildcard   // Either you ignore this match, 
         *                                                                                   or you are not the last char to match p[j], 
         *                                                                                   or you are the last to match
         */
    // clang-format on
    constexpr char any_char = '.';
    constexpr char zero_or_more = '*';
    vector<vector<bool>> dp(s.length() + 1, vector<bool>(p.length() + 1));

    // Case 1
    dp[s.length()][p.length()] = true;

    // Case 2: automatically satisfied by zero-initialisation of dp

    // Case 3
    for (int j{static_cast<int>(p.length() - 1)}; j >= 0; --j) {
      dp[s.length()][j] = j + 1 < p.length() && p[j + 1] == zero_or_more &&
                          dp[s.length()][j + 2];
    }

    for (int i{static_cast<int>(s.length()) - 1}; i >= 0; --i) {
      for (int j{static_cast<int>(p.length()) - 1}; j >= 0; --j) {
        const bool char_match{s[i] == p[j] || p[j] == any_char};
        const bool wildcard{j + 1 < p.length() && p[j + 1] == zero_or_more};

        if (char_match && !wildcard) {
          // Case 4
          dp[i][j] = dp[i + 1][j + 1];
        } else if (!char_match && wildcard) {
          // Case 5
          dp[i][j] = dp[i][j + 2];
        } else if (char_match && wildcard) {
          // Case 6
          dp[i][j] = dp[i][j + 2] || dp[i + 1][j] || dp[i + 1][j + 2];
        }
      }
    }

    return dp[0][0];
  }
};