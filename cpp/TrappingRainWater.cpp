#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
public:
    /// @brief Use the "monotonic envelope" technique.
    /// @param height The vector of building heights
    /// @return The total amount of water trapped.
    int trap(vector<int> &height)
    {
        int left{};
        int right{static_cast<int>(height.size()) - 1};
        int leftTallest{};
        int rightTallest{};
        int water{};

        while (left < right)
        {
            leftTallest = max(leftTallest, height[left]);
            rightTallest = max(rightTallest, height[right]);

            if (leftTallest <= rightTallest)
            {
                if (leftTallest > height[left])
                {
                    water += leftTallest - height[left];
                }
                ++left;
            }
            else
            {
                if (rightTallest > height[right])
                {
                    water += rightTallest - height[right];
                }
                --right;
            }
        }

        return water;
    }
};