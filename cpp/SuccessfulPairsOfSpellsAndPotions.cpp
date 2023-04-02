#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> successfulPairs(vector<int>& spells, vector<int>& potions,
                              long long success) {
    // Sort potions by strength
    sort(potions.begin(), potions.end());

    // Use binary search to find the first potion that is strong enough
    vector<int> result;
    result.reserve(spells.size());
    transform(
        spells.begin(), spells.end(), back_inserter(result),
        [&potions, &success](double spell) -> int {
          const double minimumStrength{clamp(ceil(success / spell),
                                             static_cast<double>(1),
                                             static_cast<double>(INT_MAX))};

          return static_cast<int>(distance(
              lower_bound(potions.begin(), potions.end(), minimumStrength),
              potions.end()));
        });
    return result;
  }
};