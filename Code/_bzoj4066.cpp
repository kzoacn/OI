/**************************************************************
    Problem: 4066
    User: rausen
    Language: C++
    Result: Accepted
    Time:42812 ms
    Memory:9408 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
 
using namespace std;
typedef long long ll;
const int M = 2e5 + 5;
 
int n;
ll ans;
 
inline int read(int f = 1) {
    static int x;
    static char ch;
    x = 0, ch = getchar();
    while (ch < '0' || '9' < ch)
        ch = getchar();
    while ('0' <= ch && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    //if (f) x ^= ans;
    return x;
}
 
struct point {
    int x[2], v;
     
    int& operator [] (int i) {
        return x[i];
    }
    inline bool operator == (const point &p) const {
        return x[0] == p.x[0] && x[1] == p.x[1];
    }
    inline void get() {
        x[0] = read(), x[1] = read(), v = read();
    }
};
 
struct KD_tree {
    KD_tree *son[2];
    point p;
    int mn[2], mx[2];
    ll sum;
     
    KD_tree(point _p) {
        son[0] = son[1] = NULL, p.v = sum = _p.v;
        p[0] = mn[0] = mx[0] = _p[0], p[1] = mn[1] = mx[1] = _p[1];
    }
    KD_tree() {}
     
    inline void* operator new(size_t, point _p) {
        static KD_tree mempool[M], *c = mempool;
        *c = KD_tree(_p);
        return c++; 
    }
     
    inline void update() {
        static int i;
        for (i = 0; i < 2; ++i) {
            mn[i] = mx[i] = p[i];
            if (son[0]) {
                mn[i] = min(mn[i], son[0] -> mn[i]);
                mx[i] = max(mx[i], son[0] -> mx[i]);
            }
            if (son[1]) {
                mn[i] = min(mn[i], son[1] -> mn[i]);
                mx[i] = max(mx[i], son[1] -> mx[i]);
            }
        }
        sum = p.v;
        if (son[0]) sum += son[0] -> sum;
        if (son[1]) sum += son[1] -> sum;
    }
     
    void insert(point _p, int dep) {
        if (p == _p) {
            p.v += _p.v, sum += _p.v;
            return;
        }
        bool d = _p[dep] < p[dep];
        if (!son[d]) son[d] = new(_p)KD_tree;
        else son[d] -> insert(_p, !dep);
        update();
    }
 
    inline bool in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
        return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
    }
     
    inline bool out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
        return X2 < x1 || x2 < X1 || Y2 < y1 || y2 < Y1;
    }
     
    ll query(int x1, int y1, int x2, int y2) {
        ll res = 0;
        if (in(x1, y1, x2, y2, mn[0], mn[1], mx[0], mx[1])) return sum;
        if (out(x1, y1, x2, y2, mn[0], mn[1], mx[0], mx[1])) return 0;
        if (in(x1, y1, x2, y2, p[0], p[1], p[0], p[1])) res += p.v;
        if (son[0]) res += son[0] -> query(x1, y1, x2, y2);
        if (son[1]) res += son[1] -> query(x1, y1, x2, y2);
        return res;
    }
} *T;
 
void work_add() {
    static point p;
    p.get();
    if (!T) T = new(p)KD_tree;
    else T -> insert(p, 0);
}
 
inline void work_query() {
    static int x1, y1, x2, y2;
    x1 = read(), y1 = read(), x2 = read(), y2 = read();
    if (!T) printf("%lld\n", ans = 0);
    else printf("%lld\n", ans = T -> query(x1, y1, x2, y2));
}
 
int main() {
	freopen("bzoj4066.in","r",stdin);
	freopen("bzoj4066.ans","w",stdout);
    int i, oper;
    n = read(0), ans = 0;
    while (1) {
        oper = read(0);
        if (oper == 1) work_add();
        else if (oper == 2) work_query();
        else break;
    }
    return 0;
}
