template<int ALPHABET_SIZE, unsigned char MINIMAL_CHAR>
struct AhoCorasick {
    static constexpr int NON_EXISTENT_NODE_ID = -1;
    static constexpr int FAKE_NODE_ID = 0;
    static constexpr int ROOT_ID = 1;

    int currentNode;

    vector<array<int, ALPHABET_SIZE>> edges;
    vector<int> suffixLink;
    vector<bool> isTerminal;
    vector<bool> isVisited;
    vector<int> string2Node;

    explicit AhoCorasick(const vector<string> &a) : currentNode(ROOT_ID), edges(2),
                                                    suffixLink(2, FAKE_NODE_ID),
                                                    isTerminal(2, false), isVisited(2, true),
                                                    string2Node(a.size()) {
        edges[FAKE_NODE_ID].fill(ROOT_ID);
        edges[ROOT_ID].fill(NON_EXISTENT_NODE_ID);

        for (int i = 0; i < a.size(); i++) {
            int node = ROOT_ID;
            for (unsigned char c : a[i]) {
                c -= MINIMAL_CHAR;
                if (edges[node][c] == -1) {
                    edges[node][c] = edges.size();
                    edges.emplace_back();
                    edges.back().fill(NON_EXISTENT_NODE_ID);
                    suffixLink.push_back(NON_EXISTENT_NODE_ID);
                    isTerminal.push_back(false);
                    isVisited.push_back(false);
                }
                node = edges[node][c];
            }
            isTerminal[node] = true;
            string2Node[i] = node;
        }

        queue<int> q;
        q.push(ROOT_ID);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int child = edges[node][i];
                if (child == NON_EXISTENT_NODE_ID) {
                    edges[node][i] = edges[suffixLink[node]][i];
                } else {
                    suffixLink[child] = edges[suffixLink[node]][i];
                    isTerminal[child] = isTerminal[child] | isTerminal[suffixLink[child]];
                    q.push(child);
                }
            }
        }
    }

    void apply(const string &s) {
        for (unsigned char c : s) {
            apply(c);
        }
    }

    void apply(unsigned char c) {
        c -= MINIMAL_CHAR;
        currentNode = edges[currentNode][c];
        isVisited[currentNode] = true;
    }

    void updateIsVisited() {
        for (int i = ROOT_ID; i < edges.size(); i++) {
            if (isVisited[i]) {
                int v = suffixLink[i];
                while (!isVisited[v]) {
                    isVisited[v] = true;
                    v = suffixLink[v];
                }
            }
        }
    }
};
