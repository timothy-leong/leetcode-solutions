#include <string>
using namespace std;

class Solution {
 public:
  int partitionString(string s) { return partition(s, 0, 0, 0); }

  inline int partition(string& s, const int index, const int bitset,
                       const int partitions) {
    if (index == s.length()) {
      return partitions + 1;  // + 1 for the last partition
    }

    if (const int flag{1 << static_cast<int>(s[index] - 'a')}; flag & bitset) {
      // This letter has appeared in this partition
      return partition(s, index + 1, flag, partitions + 1);
    } else {
      return partition(s, index + 1, flag | bitset, partitions);
    }
  }
};