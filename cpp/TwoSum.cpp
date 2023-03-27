#include <unordered_map>
#include <vector>
using namespace std;

/**
 * Use a hashmap to remember numbers seen before.
 * Once we find a previous number that sums to target with
 * the current number, we return the index of that number and
 * the index of the current number.
 */
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        // Map previously seen numbers to their indices.
        unordered_map<int, int> prev_nums;

        for (int i{}; i < nums.size(); ++i)
        {
            const int currNum{nums[i]};
            const int complement{target - currNum};

            if (auto iter{prev_nums.find(complement)}; iter != prev_nums.end())
            {
                return {iter->second, i};
            }

            prev_nums[currNum] = i;
        }

        return {};
    }
};