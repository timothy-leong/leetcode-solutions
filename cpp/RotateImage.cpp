#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    const int n{static_cast<int>(matrix.size())};
    const int numDiagonals{n * 2 - 1};
    // Transpose the matrix
    for (int i{}; i < numDiagonals; ++i) {
      int bottom_row{min(i, n - 1)};
      int bottom_col{max(0, i - bottom_row)};
      int top_row{bottom_col};
      int top_col{bottom_row};

      while (top_row < bottom_row) {
        swap(matrix[bottom_row][bottom_col], matrix[top_row][top_col]);
        --bottom_row;
        ++bottom_col;
        ++top_row;
        --top_col;
      }
    }
    // Reverse each row
    for (auto& row : matrix) {
      reverse(row.begin(), row.end());
    }
  }
};