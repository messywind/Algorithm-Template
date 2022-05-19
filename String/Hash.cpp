struct Hash {
    const int mod1 = 3145739, mod2 = 6291469, p1 = 2333, p2 = 131;
    vector<pair<int, int>> p, h;
    Hash(string str) : p(str.size()), h(str.size()) {
        p[0] = {1, 1};
        for (int i = 1; i < str.size(); i ++) {
            p[i] = {p[i - 1].first * p1 % mod1, p[i - 1].second * p2 % mod2};
            h[i] = {(h[i - 1].first * p1 % mod1 + str[i]) % mod1, (h[i - 1].second * p2 % mod2 + str[i]) % mod2};
        }
    }
    pair<int, int> get(int l, int r) {
        int fir = (h[r].first - h[l - 1].first * p[r - l + 1].first % mod1 + mod1) % mod1;
        int sec = (h[r].second - h[l - 1].second * p[r - l + 1].second % mod2 + mod2) % mod2;
        return {fir, sec};
    }
};
