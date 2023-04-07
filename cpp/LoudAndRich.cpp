#include <queue>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    // Create an adjacency list where a -> b iff a is richer than b
    const int n{static_cast<int>(quiet.size())};
    auto graph{adjacency_list(richer, n)};

    // Starting from vertices with indegree 0, track the lowest quietness
    // starting from that vertex and emanating outwards
    vector<int> indegrees{indegree(graph)};
    vector<int> result(n);
    queue<int> q;

    // Initialise the BFS queue
    for (int i{}; i < n; ++i) {
      result[i] = i;
      if (indegrees[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      const int curr{q.front()};
      q.pop();

      for (const auto& neighbour : graph[curr]) {
        if (quiet[result[curr]] < quiet[result[neighbour]]) {
          result[neighbour] = result[curr];
        }
        if (--indegrees[neighbour] == 0) {
          q.push(neighbour);
        }
      }
    }

    return result;
  }

 private:
  vector<vector<int>> adjacency_list(const vector<vector<int>>& richer,
                                     const int n) {
    vector<vector<int>> result(n);
    for (auto& r : richer) {
      result[r[0]].push_back(r[1]);
    }
    return result;
  }

  vector<int> indegree(const vector<vector<int>>& adjacency_list) {
    const int n{static_cast<int>(adjacency_list.size())};
    vector<int> result(n);

    for (const auto& neighbours : adjacency_list) {
      for (const auto& neighbour : neighbours) {
        result[neighbour]++;
      }
    }

    return result;
  }
};