#include <functional>
#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    vector<bool> colOccupied(n);
    // same diagonal means row - col is constant, from -n + 1 to n - 1
    vector<bool> diagonalOccupied(n * 2 - 1);
    // same antidiag means row + col is constant, from 0 to 2n - 2
    vector<bool> antidiagonalOccupied(n * 2 - 1);

    function<void(const int)> solve;
    solve = [&](const int row) {
      if (row == n) {
        result.push_back(board);
        return;  // You've found a working arrangement
      }

      for (int col{}; col < n; ++col) {
        if (colOccupied[col]) {
          continue;
        }

        const int diagonal{row - col + n - 1};
        const int antidiag{row + col};

        if (diagonalOccupied[diagonal] || antidiagonalOccupied[antidiag]) {
          continue;
        }

        // Put a queen in (row, col)
        board[row][col] = 'Q';
        colOccupied[col] = true;
        diagonalOccupied[diagonal] = true;
        antidiagonalOccupied[antidiag] = true;

        solve(row + 1);

        // Delete this queen
        board[row][col] = '.';
        colOccupied[col] = false;
        diagonalOccupied[diagonal] = false;
        antidiagonalOccupied[antidiag] = false;
      }
    };

    solve(0);
    return result;
  }
};