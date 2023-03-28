#include <vector>
using namespace std;

class Solution {
 public:
  int firstMissingPositive(vector<int>& nums) {
    for (size_t i{}; i < nums.size();) {
      // If i + 1 == nums[i], there's no need to swap.
      // If nums[nums[i] - 1] == nums[i] already, there's no need to swap also.
      if (i + 1 != nums[i] && 1 <= nums[i] && nums[i] <= nums.size() &&
          nums[nums[i] - 1] != nums[i]) {
        swap(nums[i], nums[nums[i] - 1]);
      } else {
        ++i;
      }
    }

    for (size_t i{}; i < nums.size(); ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }

    return nums.size() + 1;
  }
};