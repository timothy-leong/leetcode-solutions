#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
 public:
  int mincostTickets(vector<int>& days, vector<int>& costs) {
    unordered_map<int, int> dp;

    function<int(const int, const int)> calculate;
    calculate = [&](const int index, const int lastCoveredDay) -> int {
      if (index == days.size()) {
        return 0;  // No more travelling needed
      }

      if (lastCoveredDay >= days[index]) {
        return calculate(index + 1,
                         lastCoveredDay);  // Still covered by the last ticket
      }

      // index and lastCoveredDay are at most 9 bits
      const auto key{(index << 9) | lastCoveredDay};
      if (auto iter{dp.find(key)}; iter != dp.end()) {
        return iter->second;
      }

      // Buy a ticket for today
      return dp[key] =
                 min(costs[0] + calculate(index + 1, days[index]),
                     min(costs[1] + calculate(index + 1, days[index] + 6),
                         costs[2] + calculate(index + 1, days[index] + 29)));
    };

    return calculate(0, 0);
  }
};