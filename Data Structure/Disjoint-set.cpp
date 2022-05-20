struct DSU {
    vector<int> p, Size;
    DSU(int n) : p(n), Size(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? p[x] : p[x] = find(p[x]);
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u != v) {
            Size[v] += Size[u];
            p[u] = v;
        }
    }
};
