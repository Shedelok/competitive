namespace ImplicitTreap {
    mt19937 rnd(11);

    struct Node {
        const int y;
        Node *leftChild;
        Node *rightChild;

        int value;
        int sz;

        explicit Node(int value) : y(rnd()), leftChild(nullptr), rightChild(nullptr), value(value), sz(1) {}
    };

    Node *getNewRoot() {
        return nullptr;
    }

    bool isEmptyTree(Node *node) {
        return node == nullptr;
    }

    int getSz(Node *node) {
        return isEmptyTree(node) ? 0 : node->sz;
    }

    void push(Node *node) {
        if (isEmptyTree(node)) {
            return;
        }
    }

    void update(Node *node) {
        if (isEmptyTree(node)) {
            return;
        }
        node->sz = 1 + getSz(node->leftChild) + getSz(node->rightChild);
    }

    Node *merge(Node *smaller, Node *bigger) {
        if (smaller == nullptr) {
            return bigger;
        }
        if (bigger == nullptr) {
            return smaller;
        }
        push(smaller);
        push(bigger);
        Node *result;
        if (smaller->y > bigger->y) {
            result = smaller;
            result->rightChild = merge(smaller->rightChild, bigger);
        } else {
            result = bigger;
            result->leftChild = merge(smaller, bigger->leftChild);
        }
        update(result);
        return result;
    }

    pair<Node *, Node *> split(Node *node, int key) {
        if (node == nullptr) {
            return make_pair(nullptr, nullptr);
        }
        push(node);
        int pos = 1 + getSz(node->leftChild);
        if (pos <= key) {
            auto rec = split(node->rightChild, key - pos);
            node->rightChild = rec.first;
            update(node);
            return make_pair(node, rec.second);
        } else {
            auto rec = split(node->leftChild, key);
            node->leftChild = rec.second;
            update(node);
            return make_pair(rec.first, node);
        }
    }

    vector<Node *> multiSplit(Node *node, const initializer_list<int> &keys) {
        vector<Node *> result = {node};
        result.reserve(keys.size() + 1);
        int sum = 0;
        for (auto key : keys) {
            auto p = split(result.back(), key - sum);
            sum += key;
            result.back() = p.first;
            result.push_back(p.second);
        }
        return result;
    }

    Node *multiMerge(const initializer_list<Node *> nodes) {
        auto result = getNewRoot();
        for (auto node : nodes) {
            result = merge(result, node);
        }
        return result;
    }
}
