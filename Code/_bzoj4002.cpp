/**************************************************************
    Problem: 4002
    User: rausen
    Language: C++
    Result: Accepted
    Time:48 ms
    Memory:1272 kb
****************************************************************/
 
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
 
using namespace std;
typedef unsigned long long ll;
const ll mod = 7528443412579576937ull;
 
template <class T> T sqr(T x) {
    return x * x;
}
 
template <class T> T mul(T x, T y) {
    static T res;
    if (x < y) swap(x, y);
    res = 0;
    while (y) {
        if (y & 1) res = (res + x) % mod;
        x = (x << 1) % mod, y >>= 1;
    }
    return res;
}
 
ll b, d, n;
 
struct mat {
    ll x[3][3];
     
    inline void clear() {
        memset(x, 0, sizeof(x));
    }
    inline void one() {
        memset(x, 0, sizeof(x));
        x[1][1] = x[2][2] = 1;
    }
    inline void pre() {
        this -> clear();
        x[1][1] = 0, x[1][2] = (d - sqr(b)) >> 2, x[2][1] = 1, x[2][2] = b;
    }
     
    inline ll* operator [] (int i) {
        return x[i];
    }
     
    inline mat operator * (const mat &p) const {
        static mat res;
        static int i, j, k;
        for (res.clear(), i = 1; i <= 2; ++i)
            for (j = 1; j <= 2; ++j)
                for (k = 1; k <= 2; ++k)
                    res[i][j] = (res[i][j] + mul(x[i][k], p.x[k][j])) % mod;
        return res;
    }
    inline mat& operator *= (const mat &p) {
        return *this = *this * p;
    }
} a;
 
inline mat pow(const mat &p, ll y) {
    static mat x, res;
    res.one(), x = p;
    while (y) {
        if (y & 1) res *= x;
        x *= x, y >>= 1;
    }
    return res;
}
 
int main() {
    cin >> b >> d >> n;
    a.pre();
    a = pow(a, n);
    cout << (((a[1][1] << 1) % mod + mul(b, a[2][1]) - (d != sqr(b) && !(n & 1))) % mod + mod) % mod << endl;
    return 0;
}
