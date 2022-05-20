vector<int> color(n + 1);
function<int(int, int)> dfs = [&](int u, int c) {
    color[u] = c;
    for (auto j : g[u]) {
        if (!color[j] && !dfs(j, 3 - c) || color[j] == c) {
            return 0;
        }
    }
    return 1;
};
for (int i = 1; i <= n; i ++) {
    if (!color[i] && !dfs(i, 1)) {
        cout << "No" << endl;
        return 0;
    }
}
cout << "Yes" << endl;
