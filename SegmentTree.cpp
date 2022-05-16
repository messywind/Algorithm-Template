struct SegmentTree {
    struct Info {
        int l, r;
    };
    vector<Info> tr;
    SegmentTree(int n) : tr(n << 2) {
        function<void(int, int, int)> build = [&](int u, int l, int r) {
            if (l == r) {
                tr[u] = {l, r};
            } else {
                tr[u] = {l, r};
                int mid = l + r >> 1;
                build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
                pushup(u);
            }
        };
        build(1, 1, n);
    }
    void pushdown(int u) {

    }
    void pushup(int u) {

    }
    void modify(int u, int l, int r, int c) {
        if (tr[u].l >= l && tr[u].r <= r) {
            return ;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, c);
        if (r > mid) modify(u << 1 | 1, l, r, c);
        pushup(u);
    }
    int ask(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return ;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1, res = 0;
        if (l <= mid) res = ask(u << 1, l, r);
        if (r > mid) res = ask(u << 1 | 1, l, r);
        return res;
    }
};
