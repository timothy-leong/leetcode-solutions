#include <vector>
using namespace std;

class Solution {
 public:
  // clang-format off
    /**
     * Let dp[i][coins] refer to the maximum attainable value from
     * choosing at most `coins` coins from the leftmost `i` piles.
     * We want dp[piles.size()][k].
     * 
     * dp[i][coins] =
     * | 0                                                      if i == 0 or coins == 0
     * | max(dp[i - 1][coins - c]) + sum(piles[i - 1][c - 1]) 
     * | for c in [0..min(piles[i - 1].size(), coins)]          otherwise
     *
     * You can either take no coins from the ith pile, or you can take up to `coins`
     * number of coins or the total number of coins in the ith pile, whichever number
     * is lower.
     */
  // clang-format on
  int maxValueOfCoins(vector<vector<int>>& piles, int k) {
    const int n{static_cast<int>(piles.size())};
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));

    for (int i{1}; i <= n; ++i) {
      for (int coins{}; coins <= k; ++coins) {
        int currentSum{};
        const int maxCoinsDrawable{
            min(static_cast<int>(piles[i - 1].size()), coins)};
        dp[i][coins] = dp[i - 1][coins];
        for (int takeFromCurrPile{1}; takeFromCurrPile <= maxCoinsDrawable;
             ++takeFromCurrPile) {
          currentSum += piles[i - 1][takeFromCurrPile - 1];
          dp[i][coins] = max(dp[i][coins],
                             dp[i - 1][coins - takeFromCurrPile] + currentSum);
        }
      }
    }
    return dp[n][k];
  }
};