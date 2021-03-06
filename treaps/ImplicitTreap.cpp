namespace ImplicitTreap {
    struct Node {
        static mt19937 rnd;

        const int y;
        Node *leftChild;
        Node *rightChild;

        int value;
        int sz;

        explicit Node(int value) : y(rnd()), leftChild(nullptr), rightChild(nullptr), value(value), sz(1) {}

        static Node *getNewRoot() {
            return nullptr;
        }

        static bool isEmptyTree(Node *node) {
            return node == nullptr;
        }

        static int getSz(Node *node) {
            return isEmptyTree(node) ? 0 : node->sz;
        }

        static void push(Node *node) {
            if (isEmptyTree(node)) {
                return;
            }
        }

        static void update(Node *node) {
            if (isEmptyTree(node)) {
                return;
            }
            node->sz = 1 + getSz(node->leftChild) + getSz(node->rightChild);
        }

        static Node *merge(Node *smaller, Node *bigger) {
            if (isEmptyTree(smaller)) {
                return bigger;
            }
            if (isEmptyTree(bigger)) {
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

        static pair<Node *, Node *> split(Node *node, int key) {
            if (isEmptyTree(node)) {
                return make_pair(getNewRoot(), getNewRoot());
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

        static vector<Node *> multiSplit(Node *node, const initializer_list<int> &keys) {
            vector<Node *> result = {node};
            result.reserve(keys.size() + 1);
            int prev = 0;
            for (auto key : keys) {
                auto p = split(result.back(), key - prev);
                prev = key;
                result.back() = p.first;
                result.push_back(p.second);
            }
            return result;
        }

        static Node *multiMerge(const initializer_list<Node *> nodes) {
            auto result = getNewRoot();
            for (auto node : nodes) {
                result = merge(result, node);
            }
            return result;
        }
    };

    mt19937 Node::rnd(11);
}
