struct Fenwick {
    int n;
    vector<int> tr;
    Fenwick(int n) : n(n), tr(n) {}
    void modify(int x, int c) {
        for (int i = x + 1; i <= n; i += i & -i) tr[i - 1] += c;
    }
    int ask(int x) {
        int res = 0;
        for (int i = min(x + 1, n); i; i -= i & -i) res += tr[i - 1];
        return res;
    }
};
