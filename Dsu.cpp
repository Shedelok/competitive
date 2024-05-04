struct Dsu {
  vector<int> _dsu;
  vector<int> _sz;

  explicit Dsu(int n): _dsu(n), _sz(n, 1) {
    iota(_dsu.begin(), _dsu.end(), 0);
  }

  int get(int v) {
    return _dsu[v] == v ? v : _dsu[v] = get(_dsu[v]);
  }

  void un(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) {
      return;
    }
    if (_sz[a] < _sz[b]) {
      swap(a, b);
    }
    _dsu[b] = a;
    _sz[a] += _sz[b];
  }

  inline bool same(int a, int b) {
    return get(a) == get(b);
  }
};

/*
int main() { // Dsu
  Dsu dsu(5);
  for (int i = 0; i < 5; i++) cout << dsu.get(i) << ' '; cout << endl; // 0 1 2 3 4
  dsu.un(0, 1);
  dsu.un(3, 4);
  for (int i = 0; i < 5; i++) cout << dsu.get(i) << ' '; cout << endl; // 0 0 2 3 3
  cout << dsu.same(0, 2) << endl; // 0
  cout << dsu.same(4, 3) << endl; // 1
}
*/

