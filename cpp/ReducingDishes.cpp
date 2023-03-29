#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  int maxSatisfaction(vector<int>& satisfaction) {
    sort(satisfaction.begin(), satisfaction.end());

    // Find the first dish with satisfaction >= 0
    int satisfactionDelta{};
    int i = satisfaction.size() - 1;
    for (; i >= 0 && satisfactionDelta + satisfaction[i] >= 0; --i) {
      satisfactionDelta += satisfaction[i];
    }

    // i points to the first dish you don't want.
    int result{}, minute{1};
    for (int j = i + 1; j < satisfaction.size(); ++j) {
      result += satisfaction[j] * minute++;
    }

    return result;
  }
};