#include <functional>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    /**
     * An inner function that takes both lists and the carry digit
     * and sums them.
     *
     * The input lists are not mutated, which results in
     * a performance penalty. Check with your interviewer if it is ok to
     * override an existing list to save memory.
     */
    function<ListNode*(const ListNode*, const ListNode*, int)> sumLists;
    sumLists = [&](const ListNode* first, const ListNode* second,
                   int carry) -> ListNode* {
      // Base case: No nodes and carry digit is 0
      if (!first && !second && !carry) {
        return nullptr;
      }

      const int firstNumber{first ? first->val : 0};
      const int secondNumber{second ? second->val : 0};
      const int sum{firstNumber + secondNumber + carry};

      return new ListNode(sum % 10,
                          sumLists(first ? first->next : nullptr,
                                   second ? second->next : nullptr, sum / 10));
    };

    return sumLists(l1, l2, 0);
  }
};