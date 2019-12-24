namespace SuffixArrayWithLcp {
    int n;
    string s;
    vector<int> array;

    vector<int> suffixArray() {
        vector<int> result(n);
        vector<int> &eqClass = array;
        vector<int> newResult(n);
        vector<int> newEqClass(n);
        for (int i = 0; i < n; i++) {
            result[i] = i;
        }
        sort(result.begin(), result.end(), [&](int a, int b) {
            return s[a] < s[b];
        });
        for (int i = 0, x = 0; i < n; i++) {
            if (i > 0 && s[result[i]] != s[result[i - 1]]) {
                x++;
            }
            eqClass[result[i]] = x;
        }
        for (int pw = 1; pw < n; pw *= 2) {
            vector<int> pos(n, 0);
            for (auto x : eqClass) {
                if (x < n - 1) {
                    pos[x + 1]++;
                }
            }
            for (int i = 1; i < n; i++) {
                pos[i] += pos[i - 1];
            }
            for (int i = 0; i < n; i++) {
                int id = result[i] - pw;
                if (id < 0) {
                    id += n;
                }
                newResult[pos[eqClass[id]]++] = id;
            }
            newEqClass[newResult[0]] = 0;
            for (int i = 1, x = 0; i < n; ++i) {
                if (eqClass[newResult[i - 1]] == eqClass[newResult[i]]) {
                    int r1 = newResult[i - 1] + pw;
                    if (r1 > n) {
                        r1 -= n;
                    }
                    int r2 = newResult[i] + pw;
                    if (r2 > n) {
                        r2 -= n;
                    }
                    x += eqClass[r1] != eqClass[r2];
                } else {
                    x++;
                }
                newEqClass[newResult[i]] = x;
            }
            result.swap(newResult);
            eqClass.swap(newEqClass);
            if (eqClass[result.back()] == n - 1) {
                break;
            }
        }
        return result;
    }

    vector<int> lcps(const vector<int> &a) {
        vector<int> result(n - 1, 0);
        vector<int> &pos = array;
        for (int i = 0; i < n; i++) {
            pos[a[i]] = i;
        }
        int cur = 0;
        for (int id = 0; id < n; id++) {
            cur = max(cur - 1, 0);
            if (pos[id] != 0) {
                while (s[id + cur] == s[a[pos[id] - 1] + cur]) {
                    cur++;
                }
                result[pos[id] - 1] = cur;
            }
        }
        return result;
    }

    pair<vector<int>, vector<int>> get(const string &input) {
        s = input + char(0);
        n = s.size();
        array.resize(n);
        vector<int> sA = suffixArray();
        sA.erase(sA.begin());
        n--;
        return {sA, lcps(sA)};
    }
}
