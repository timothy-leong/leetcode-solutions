#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
 public:
  int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    function<int(const int, const int, const int)> go;
    go = [&](const int i, const int j, const int result) {
      if (i > j) return result;
      if (i == j) return go(i + 1, j, result + 1);
      return go(i + (people[i] + people[j] <= limit ? 1 : 0), j - 1,
                result + 1);
    };
    return go(0, people.size() - 1, 0);
  }
};