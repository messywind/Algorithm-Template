using i64 = long long;
constexpr int mod = 998244353;
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
template<int mod>
struct ModInt {
    int x;
    ModInt() : x(0) {}
    ModInt(i64 y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    ModInt &operator+=(const ModInt &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &p) {
        *this *= p.inv();
        return *this;
    }
    ModInt operator-() const {
        return ModInt(-x);
    }
    ModInt operator+(const ModInt &p) const {
        return ModInt(*this) += p;
    }
    ModInt operator-(const ModInt &p) const {
        return ModInt(*this) -= p;
    }
    ModInt operator*(const ModInt &p) const {
        return ModInt(*this) *= p;
    }
    ModInt operator/(const ModInt &p) const {
        return ModInt(*this) /= p;
    }
    bool operator==(const ModInt &p) const {
        return x == p.x;
    }
    bool operator!=(const ModInt &p) const {
        return x != p.x;
    }
    ModInt inv() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }
    ModInt pow(i64 n) const {
        ModInt res(1), mul(x);
        while (n > 0) {
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }
    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }
    friend istream &operator>>(istream &is, ModInt &a) {
        i64 t;
        is >> t;
        a = ModInt<mod>(t);
        return (is);
    }
    int val() const {
        return x;
    }
    static constexpr int val_mod() {
        return mod;
    }
};
using Z = ModInt<mod>;
struct Hash {
    const int p1 = 2333, p2 = 131;
    vector<pair<ModInt<3145739>, ModInt<6291469>>> p, h;
    Hash(string str) : p(str.size()), h(str.size()) {
        p[0] = {1, 1};
        for (int i = 1; i < str.size(); i ++) {
            p[i] = {p[i - 1].first * p1, p[i - 1].second * p2};
            h[i] = {h[i - 1].first * p1 + str[i], h[i - 1].second * p2 + str[i]};
        }
    }
    pair<int, int> get(int l, int r) {
        auto fir = h[r].first - h[l - 1].first * p[r - l + 1].first;
        auto sec = h[r].second - h[l - 1].second * p[r - l + 1].second;
        return {fir.val(), sec.val()};
    }
};
