template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void modify(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T ask(int x) {
        T ans = 0;
        for (int i = min(x + 1, n); i; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
};
