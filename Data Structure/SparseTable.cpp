struct ST {
    vector<vector<int>> f, g, h;
    ST(int n, vector<int> a) : f(n, vector<int>(__lg(n) + 1)), g(n, vector<int>(__lg(n) + 1)), h(n, vector<int>(__lg(n) + 1)) {
        for (int i = 1; i < n; i ++) {
            f[i][0] = g[i][0] = h[i][0] = a[i];
        }
        for (int j = 1; (1ll << j) < n; j ++) {
            for (int i = 1; i + (1ll << j) - 1 < n; i ++) {
                f[i][j] = max(f[i][j - 1], f[i + (1ll << (j - 1))][j - 1]);
                g[i][j] = min(g[i][j - 1], g[i + (1ll << (j - 1))][j - 1]);
                h[i][j] = __gcd(h[i][j - 1], h[i + (1ll << (j - 1))][j - 1]);
            }
        }
    }
    int askMax(int l, int r) {
        int k = __lg(r - l + 1);
        return max(f[l][k], f[r - (1ll << k) + 1][k]);
    }
    int askMin(int l, int r) {
        int k = __lg(r - l + 1);
        return min(g[l][k], g[r - (1ll << k) + 1][k]);
    }
    int askGcd(int l, int r) {
        int k = __lg(r - l + 1);
        return __gcd(h[l][k], h[r - (1ll << k) + 1][k]);
    }
};
