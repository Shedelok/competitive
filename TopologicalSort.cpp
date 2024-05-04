namespace TopologicalSort {
  void _dfs(int v, const vector<vector<int>>& g, vector<bool>& visited, vector<int>& result) {
    visited[v] = true;
    for (int to : g[v]) {
      if (!visited[to]) {
        _dfs(to, g, visited, result);
      }
    }
    result.push_back(v);
  }

  vector<int> drains_to_sources(const vector<vector<int>> &g) {
    const int n = g.size();
    vector<bool> visited(n, false);
    vector<int> result;
    result.reserve(n);
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        _dfs(i, g, visited, result);
      }
    }
    return result;
  }

  inline vector<int> sources_to_drains(const vector<vector<int>> &g) {
    auto result = drains_to_sources(g);
    reverse(result.begin(), result.end());
    return result;
  }
}

/*
int main() { // TopologicalSort
  vector<vector<int>> g(4);
  g[0] = {1, 2};
  g[1] = g[2] = {3};
  for (int v : TopologicalSort::drains_to_sources(g)) cout << v << ' '; cout << endl; // 3 1 2 0
  for (int v : TopologicalSort::sources_to_drains(g)) cout << v << ' '; cout << endl; // 0 2 1 3
}
*/

