#include <algorithm>
#include <functional>
#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    // Track characters in our current substring window
    vector<bool> charactersInWindow(128);

    /**
     * @brief Performs the "sliding window" technique
     * @param begin The start of the window
     * @param end One past the end of the window
     * @param longest The length of the longest substring seen
     */
    function<int(const int, const int, const int)> find;
    find = [&](const int begin, const int end, const int longest) {
      if (end == s.length()) {
        return longest;
      }

      const int currLetter{static_cast<int>(s[end])};

      // If this letter is in the window already,
      // we delete letters from the left until
      // there are no more occurrences of currLetter
      if (charactersInWindow[currLetter]) {
        charactersInWindow[s[begin]] = false;
        return find(begin + 1, end, longest);
      }

      // Insert this character into the window
      charactersInWindow[currLetter] = true;
      return find(begin, end + 1, max(longest, end + 1 - begin));
    };

    return find(0, 0, 0);
  }
};