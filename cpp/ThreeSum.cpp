#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());

    function<void(const int, const int, const int)> twoSum;
    twoSum = [&](const int begin, const int end, const int target) {
      if (begin >= end) {
        return;
      } else if (auto sum{nums[begin] + nums[end]}; sum == target) {
        result.push_back({-target, nums[begin], nums[end]});

        // Don't repeat the second number
        auto iter{
            upper_bound(nums.begin() + begin, nums.begin() + end, nums[begin])};
        twoSum(begin + distance(nums.begin() + begin, iter), end - 1, target);
      } else if (sum < target) {
        twoSum(begin + 1, end, target);
      } else {
        twoSum(begin, end - 1, target);
      }
    };

    function<void(const int)> run;
    run = [&](const int firstPos) {
      if (firstPos == nums.size()) {
        return;
      }

      // Don't repeat the first number
      if (firstPos == 0 || nums[firstPos] != nums[firstPos - 1]) {
        twoSum(firstPos + 1, nums.size() - 1, -nums[firstPos]);
      }

      run(firstPos + 1);
    };

    run(0);
    return result;
  }
};