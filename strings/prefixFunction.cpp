vector<int> prefixFunction(const string &s) {
    vector<int> result(s.size());
    result[0] = 0;
    for (int i = 1; i < s.size(); i++) {
        result[i] = result[i - 1];
        while (result[i] > 0 && s[i] != s[result[i]]) {
            result[i] = result[result[i] - 1];
        }
        result[i] += s[i] == s[result[i]];
    }
    return result;
}
