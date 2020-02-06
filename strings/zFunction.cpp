vector<int> zFunction(const string &s) {
    vector<int> result(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (i <= r) {
            result[i] = min(r - i + 1, result[i - l]);
        }
        while (i + result[i] < s.size() && s[result[i]] == s[i + result[i]]) {
            result[i]++;
        }
        if (i + result[i] - 1 > r) {
            l = i;
            r = i + result[i] - 1;
        }
    }
    return result;
}
