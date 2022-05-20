vector<int> st(n1 + n2 + 1), match(n1 + n2 + 1);
function<int(int)> find = [&](int u) {
    for (auto j : g[u]) {
        if (!st[j]) {
            st[j] = 1;
            if (!match[j] || find(match[j])) {
                match[j] = u;
                return 1;
            }
        }
    }
    return 0;
};
int res = 0;
for (int i = 1; i <= n1; i ++) {
    fill(st.begin(), st.end(), 0);
    if (find(i)) {
        res ++;
    }
}
