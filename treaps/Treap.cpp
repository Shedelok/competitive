namespace Treap {
    mt19937 rnd(11);

    struct Node {
        int x;
        int y;
        Node *leftChild;
        Node *rightChild;

        long long sum;

        explicit Node(int x) : x(x), y(rnd()), leftChild(nullptr), rightChild(nullptr), sum(x) {}
    };

    Node *getNewRoot() {
        return nullptr;
    }

    bool isEmptyTree(Node *node) {
        return node == nullptr;
    }

    void push(Node *node) {

    }

    void update(Node *node) {
        node->sum = node->x
                    + (node->leftChild == nullptr ? 0 : node->leftChild->sum)
                    + (node->rightChild == nullptr ? 0 : node->rightChild->sum);
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
        if (node->x <= key) {
            auto rec = split(node->rightChild, key);
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
}
