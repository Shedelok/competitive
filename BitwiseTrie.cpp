template<typename T>
struct BitwiseTrie {
  struct Node {
    array<Node*, 2> children;

    Node() : children({nullptr, nullptr}) {}

    inline bool isLeaf() {
      return children[0] == nullptr && children[1] == nullptr;
    }

    void visit(T x) {
    }

    void terminate(T x) {
      visit(x);
    }
  };

  const int bits;
  Node* const root;

  explicit BitwiseTrie(int bits): bits(bits), root(new Node()) {}

  void add(T x) {
    Node* curNode = root;
    for (int i = bits - 1; i >= 0; i--) {
      curNode->visit(x);
      int ind = (x >> i) & 1;
      if (curNode->children[ind] == nullptr) {
        curNode->children[ind] = new Node();
      }
      curNode = curNode->children[ind];
    }
    curNode->terminate(x);
  }
};

/*
int main() { // BitwiseTrie
  BitwiseTrie<int> tree(3);
  tree.add(0b111);
  tree.add(0b001);
  tree.add(0b000);
  auto* x = tree.root;
  cout << (x->children[0] == nullptr) << endl; // 0
  x = x->children[1];
  cout << (x->children[0] == nullptr) << endl; // 1
}
*/

