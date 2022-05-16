#include <bits/stdc++.h>
#define int long long
#define poly vector<int>
#define len(x) ((int)x.size())
using namespace std;
const int N = 3e5 + 5, G = 3, Ginv = 332748118, mod = 998244353;
int rev[N], lim, w, k;
struct nd {
    int x, y;
    nd (int a = 0, int b = 0) {
        x = a, y = b;
    }
    nd operator * (const nd &a) const {
        return nd((x * a.x % mod + y * a.y % mod * w % mod) % mod, (x * a.y % mod + y * a.x % mod) % mod);
    }
};
int readmod() {
    int x = 0;
    char s = getchar();
    while (s < '0' || s > '9') s = getchar();
    while (s >= '0' && s <= '9') {
        x = ((x << 1) + (x << 3) + (s - '0')) % mod;
        s = getchar();
    }
    return x;
}
int qmi(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
nd qmi(nd a, int b) {
    nd res = nd(1, 0);
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
bool check_sqrt(int a) {
    return qmi(a, (mod - 1) / 2) == 1;
}
int get_w(int n) {
    for (int a = rand(); ; a = rand()) {
        if (!check_sqrt((a * a % mod - n + mod) % mod)) {
            return w = (a * a % mod - n + mod) % mod, a;
        }
    }
}
int get_sqrt(int n) {
    int a = get_w(n), x_1 = (qmi(nd(a, 1), (mod + 1) / 2)).x, x_2 = mod - x_1;
    return x_1 < x_2 ? x_1 : x_2;
}
void polyinit(int n) {
    for (lim = 1; lim < n; lim <<= 1);
    for (int i = 0; i < lim; i ++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? lim >> 1 : 0);
}
void NTT(poly &f, int op) {
    for (int i = 0; i < lim; i ++) {
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    }
    for (int mid = 1; mid < lim; mid <<= 1) {
        int Gn = qmi(op == 1 ? G : Ginv, (mod - 1) / (mid << 1));
        for (int i = 0; i < lim; i += mid * 2) {
            for (int j = 0, G0 = 1; j < mid; j ++, G0 = G0 * Gn % mod) {
                int x = f[i + j], y = G0 * f[i + j + mid] % mod;
                f[i + j] = (x + y) % mod, f[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
    if (op == -1) {
        int inv = qmi(lim, mod - 2);
        for (int i = 0; i < lim; i ++) f[i] = f[i] * inv % mod;
    }
}
poly operator + (poly f, int x) {
    f[0] = (f[0] + x) % mod;
    return f;
}
poly operator - (poly f, int x) {
    f[0] = (f[0] - x + mod) % mod;
    return f;
}
poly operator * (poly f, int x) {
    for (int i = 0; i < len(f); i ++) f[i] = f[i] * x % mod;
    return f;
}
poly operator + (poly f, poly g) {
    poly res = f;
    res.resize(max(len(f), len(g)));
    for (int i = 0; i < len(g); i ++) res[i] = (res[i] + g[i]) % mod;
    return res;
}
poly operator - (poly f, poly g) {
    poly res = f;
    res.resize(max(len(f), len(g)));
    for (int i = 0; i < len(g); i ++) res[i] = (res[i] - g[i] + mod) % mod;
    return res;
}
poly operator * (poly f, poly g) {
    int n = len(f) + len(g) - 1;
    polyinit(n), f.resize(lim), g.resize(lim);
    NTT(f, 1), NTT(g, 1);
    for (int i = 0; i < lim; i ++) f[i] = f[i] * g[i] % mod;
    NTT(f, -1), f.resize(n);
    return f;
}
poly polyinv(poly f, int n) {
    poly res(1, qmi(f[0], mod - 2)), t;
    for (int len = 2; len < n << 1; len <<= 1) {
        t.resize(len), polyinit(len << 1);
        for (int i = 0; i < len; i ++) t[i] = i < len(f) ? f[i] : 0;
        t.resize(lim), res.resize(lim);
        NTT(t, 1), NTT(res, 1);
        for (int i = 0; i < lim; i ++) res[i] = res[i] * (2 - res[i] * t[i] % mod + mod) % mod;
		NTT(res, -1), res.resize(len);
    }
    res.resize(n);
    return res;
}
pair<poly, poly> polydiv(poly f, poly g) {
    int n = len(f) - len(g) + 1;
    poly q = f;
    reverse(q.begin(), q.end()), q.resize(n);
    reverse(g.begin(), g.end());
    q = q * polyinv(g, n), q.resize(n);
    reverse(q.begin(), q.end()), reverse(g.begin(), g.end());
    poly r = f - g * q;
    return {q, r};
}
poly polysqrt(poly f, int n) {
    int inv2 = qmi(2, mod - 2);
    poly b(1, get_sqrt(f[0])), c, d;
    for (int len = 4; (len >> 2) < n; len <<= 1) {
        c = f, c.resize(len >> 1), polyinit(len);
        d = polyinv(b, len >> 1);
        c.resize(lim), d.resize(lim);
        NTT(c, 1), NTT(d, 1);
        for (int i = 0; i < lim; i ++) c[i] = c[i] * d[i] % mod;
        NTT(c, -1);
        b.resize(len >> 1);
        for (int i = 0; i < (len >> 1); i ++) b[i] = (c[i] + b[i]) % mod * inv2 % mod;
    }
    b.resize(lim);
    if (mod - b[0] < b[0]) {
        for (int i = 0; i < len(b); i ++) b[i] = (0 - b[i] + mod) % mod;
    }
    return b;
}
poly polyderiv(poly f) {
    for (int i = 0; i < len(f) - 1; i ++) f[i] = f[i + 1] * (i + 1) % mod;
    f.pop_back();
    return f;
}
poly polyinteg(poly f) {
    for (int i = len(f) - 1; i; i --) f[i] = f[i - 1] * qmi(i, mod - 2) % mod;
    f[0] = 0;
    return f;
}
poly polyln(poly f, int n) {
    f = polyinteg(polyderiv(f) * polyinv(f, n));
    f.resize(n);
    return f;
}
poly polyexp(poly f, int n) {
    poly b(1, 1), c;
    for (int len = 2; (len >> 1) < n; len <<= 1) {
        c = polyln(b, len);
        for (int i = 0; i < len; i ++) c[i] = ((i < len(f) ? f[i] : 0) - c[i] + mod) % mod;
        c = c + 1, b = b * c;
        b.resize(len);
    }
    b.resize(n);
    return b;
}
poly polyqmi(poly f, int n, int k) {
    f = polyexp(polyln(f, n) * k, n);
    return f;
}
poly dc(int l, int r) {
    if (l == r) return f;
    int mid = l + r >> 1;
    return dc(l, mid) * dc(mid + 1, r);
}
signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
}
