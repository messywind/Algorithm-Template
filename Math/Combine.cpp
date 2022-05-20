vector<int> fact, infact;
void init(int n) {
    fact.resize(n + 1), infact.resize(n + 1);
    fact[0] = infact[0] = 1;
    for (int i = 1; i <= n; i ++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    infact[n] = qmi(fact[n], mod - 2);
    for (int i = n; i; i --) {
        infact[i - 1] = infact[i] * i % mod;
    }
}
int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fact[n] * infact[n - m] % mod * infact[m] % mod;
}
