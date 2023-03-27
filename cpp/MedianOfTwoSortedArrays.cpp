#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution
{
public:
    /**
     * @brief We need to make the following observations:
     * 1. Some prefix of nums1 and some prefix of nums2 make up the left half of the final array
     * 2. We know the length of the left half of the final array, and therefore we know the length of the right half.
     * 3. Suppose we knew which prefix of nums1 and nums2 were in the left half. Then if we partition the two arrays as follows:
     *  nums1 = [... x1 (last number in left half), x2(first number in right half), ...]
     *  nums2 = [... x3 (last number in left half), x4(first number in right half), ...]
     *  Then it must be that x1 <= x4, and x3 <= x2. This is the condition that tells us if we have found the right partition.
     * @param nums1 The first sorted array
     * @param nums2 The second sorted array
     */
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        // Make nums1 the shorter array
        if (nums1.size() > nums2.size())
        {
            swap(nums1, nums2);
        }

        const int totalLength{static_cast<int>(nums1.size()) + static_cast<int>(nums2.size())};
        const bool isEvenLength{totalLength % 2 == 0};
        const int leftHalfLength{totalLength / 2}; // For odd-length arrays, the right half is one element larger

        // Do binary search on the size of nums1's prefix in the left half.
        function<double(const int, const int)> find;
        find = [&](const int lower_bound, const int upper_bound)
        {
            const int nums1PrefixSize{(lower_bound + upper_bound) >> 1};
            const int nums2PrefixSize{leftHalfLength - nums1PrefixSize};
            const int largestNumberInNums1Prefix = nums1PrefixSize == 0 ? INT_MIN : nums1[nums1PrefixSize - 1];
            const int largestNumberInNums2Prefix = nums2PrefixSize == 0 ? INT_MIN : nums2[nums2PrefixSize - 1];
            const int smallestNumberInNums1Suffix = nums1PrefixSize == nums1.size() ? INT_MAX : nums1[nums1PrefixSize];
            const int smallestNumberInNums2Suffix = nums2PrefixSize == nums2.size() ? INT_MAX : nums2[nums2PrefixSize];

            if (largestNumberInNums1Prefix <= smallestNumberInNums2Suffix && largestNumberInNums2Prefix <= smallestNumberInNums1Suffix)
            {
                // We have found the correct partition
                if (isEvenLength)
                {
                    // Take the average between the largest number on the left side and the smallest number on the right side
                    const int leftLargestNumber = max(largestNumberInNums1Prefix, largestNumberInNums2Prefix);
                    const int rightSmallestNumber = min(smallestNumberInNums1Suffix, smallestNumberInNums2Suffix);
                    return (leftLargestNumber + rightSmallestNumber) / 2.0;
                }
                else
                {
                    // Return the smallest number on the right side
                    return static_cast<double>(min(smallestNumberInNums1Suffix, smallestNumberInNums2Suffix));
                }
            }

            if (largestNumberInNums1Prefix > smallestNumberInNums2Suffix)
            {
                // nums1's prefix is too big
                return find(lower_bound, nums1PrefixSize - 1);
            }
            else
            {
                return find(nums1PrefixSize + 1, upper_bound);
            }
        };

        return find(0, nums1.size());
    }
};