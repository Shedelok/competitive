namespace PersistentImplicitTreap {
    struct Node {
        static mt19937_64 rnd;

        const Node *leftChild;
        const Node *rightChild;

        const int value;
        const unsigned long long sz;

        explicit Node(int value) : leftChild(nullptr), rightChild(nullptr), value(value), sz(1) {}

        Node(int value, const Node *leftChild, const Node *rightChild)
                : leftChild(leftChild), rightChild(rightChild), value(value),
                  sz(1 + getSz(leftChild) + getSz(rightChild)) {}

        static const Node *getNewRoot() {
            return nullptr;
        }

        static bool isEmptyTree(const Node *node) {
            return node == nullptr;
        }

        static unsigned long long getSz(const Node *node) {
            return isEmptyTree(node) ? 0 : node->sz;
        }

        static void push(const Node *node) {
            if (isEmptyTree(node)) {
                return;
            }
            // TODO
        }

        static const Node *merge(const Node *smaller, const Node *bigger) {
            if (isEmptyTree(smaller)) {
                return bigger;
            }
            if (isEmptyTree(bigger)) {
                return smaller;
            }
            push(smaller);
            push(bigger);
            if (rnd() % (smaller->sz + bigger->sz) < smaller->sz) {
                return new Node(smaller->value, smaller->leftChild, merge(smaller->rightChild, bigger));
            } else {
                return new Node(bigger->value, merge(smaller, bigger->leftChild), bigger->rightChild);
            }
        }

        static pair<const Node *, const Node *> split(const Node *node, unsigned long long key) {
            if (isEmptyTree(node)) {
                return make_pair(getNewRoot(), getNewRoot());
            }
            push(node);
            auto pos = 1 + getSz(node->leftChild);
            if (pos <= key) {
                auto rec = split(node->rightChild, key - pos);
                return make_pair(new Node(node->value, node->leftChild, rec.first), rec.second);
            } else {
                auto rec = split(node->leftChild, key);
                return make_pair(rec.first, new Node(node->value, rec.second, node->rightChild));
            }
        }

        static vector<const Node *> multiSplit(const Node *node, const initializer_list<unsigned long long> &keys) {
            vector<const Node *> result = {node};
            result.reserve(keys.size() + 1);
            unsigned long long prev = 0;
            for (auto key : keys) {
                auto p = split(result.back(), key - prev);
                prev = key;
                result.back() = p.first;
                result.push_back(p.second);
            }
            return result;
        }

        static const Node *multiMerge(const initializer_list<const Node *> nodes) {
            auto result = getNewRoot();
            for (auto node : nodes) {
                result = merge(result, node);
            }
            return result;
        }
    };

    mt19937_64 Node::rnd(11);
}
