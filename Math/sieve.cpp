int cnt = 0;
vector<int> primes(n + 1), euler(n + 1), mobius(n + 1);
vector<bool> st(n + 1);
auto sieve = [&](int n) {
    euler[1] = mobius[1] = 1;
    for (int i = 2; i <= n; i ++) {
        if (!st[i]) {
            primes[cnt ++] = i;
            euler[i] = i - 1;
            mobius[i] = -1;
        }
        for (int j = 0; i * primes[j] <= n; j ++) {
            int t = i * primes[j];
            st[t] = 1;
            if (i % primes[j] == 0) {
                mobius[t] = 0;
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
            mobius[t] = -mobius[i];
        }
    }
};
sieve(n);
