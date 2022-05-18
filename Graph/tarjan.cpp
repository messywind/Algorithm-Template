int timestamp = 0, scc_cnt = 0;
vector<int> dfn(n + 1), low(n + 1), Size(n + 1), id(n + 1), st(n + 1), s;
function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++ timestamp;
    s.push_back(u), st[u] = 1;
    for (auto j : g[u]) {
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (st[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        scc_cnt ++;
        int v;
        do {
            v = s.back();
            s.pop_back();
            st[v] = 0;
            id[v] = scc_cnt;
            Size[scc_cnt] ++;
        } while (u != v);
    }
};
for (int i = 1; i <= n; i ++) {
    if (!dfn[i]) {
        tarjan(i);
    }
}
