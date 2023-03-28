#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
 public:
  /// @brief Use the "monotonic envelope" technique.
  /// @param height The vector of building heights
  /// @return The total amount of water trapped.
  int trap(vector<int>& height) {
    function<int(const int, const int, const int, const int, const int)> go;
    go = [&](const int left, const int right, const int prevLeftTallest,
             const int prevRightTallest, const int water) -> int {
      if (left >= right) {
        return water;
      }

      const int currLeftTallest = max(prevLeftTallest, height[left]);
      const int currRightTallest = max(prevRightTallest, height[right]);

      if (currLeftTallest <= currRightTallest) {
        return go(left + 1, right, currLeftTallest, currRightTallest,
                  water + max(currLeftTallest - height[left], 0));
      }

      return go(left, right - 1, currLeftTallest, currRightTallest,
                water + max(currRightTallest - height[right], 0));
    };

    return go(0, height.size() - 1, 0, 0, 0);
  }
};