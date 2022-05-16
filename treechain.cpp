vector<int> dep(n + 1), fa(n + 1), Size(n + 1), son(n + 1);
function<void(int, int, int)> dfs1 = [&](int u, int father, int depth) {
    dep[u] = depth, fa[u] = father, Size[u] = 1;
    for (auto j : g[u]) {
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        Size[u] += Size[j];
        if (Size[son[u]] < Size[j]) son[u] = j;
    }
};
int cnt = 0;
vector<int> top(n + 1), id(n + 1);
function<void(int, int)> dfs2 = [&](int u, int t) {
    id[u] = ++ cnt, top[u] = t;
    if (!son[u]) return ;
    dfs2(son[u], t);
    for (auto j : g[u]) {
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
};
dfs1(1, -1, 1), dfs2(1, 1);
SegmentTree tr(n + 1);
auto modify_path = [&](int u, int v, int c) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        tr.modify(1, id[top[u]], id[u], c);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    tr.modify(1, id[v], id[u], c);
};
auto ask_path = [&](int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += tr.ask(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += tr.ask(1, id[v], id[u]);
    return res;
};
auto lca = [&](int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
};
