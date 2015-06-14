/** 
* @Author:kAc @ Qingdao No.2 Middle School
* @Version:1.0.0
* Data Generation Program For Shandong Team Selection Contest Round 1 Day 1 Problem 2
*/ 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <string>
using namespace std;
const int INF = 0x7fffffff;
const int N[20] = {4000, 200, 
                   40000, 40000, 80000, 80000, 
                   80000, 80000, 80000, 
                   40000, 40000, 80000, 80000, 
                   40000, 40000, 80000, 80000, 
                   40000, 80000, 80000};
const bool hasL[20] ={1, 1, 
                      0, 0, 0, 0, 
                      0, 0, 0, 
                      1, 1, 1, 1, 
                      0, 0, 0, 0, 
                      1, 1, 1};
const int K[20] = {INF, INF,
                   INF, INF, INF, INF, 
                   1, 1, 1, 
                   1, 1, 1, 1, 
                   INF, INF, INF, INF, 
                   INF, INF, INF};
const bool isChain[20]={0, 0,
                        1, 1, 1, 1,
                        0, 0, 0, 
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0};
int Rand() { return rand() << 15 ^ rand(); }
pair<int, int>edge[1000001]; int tot;
struct Tuf{
	int f[100001];
	int find(int a) { return f[a] == a ? a : f[a] = find(f[a]); }
	void merge(int a, int b) { a = find(a); b = find(b); f[a] = b; }
	bool same(int a, int b) { return find(a) == find(b); }
} uf;
int dep[1000001], f[1000001][20];
int p[1000001];
int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y); int k = dep[x] - dep[y];
    for (int i = 0; i < 20; i++) if ((k >> i) & 1) x = f[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}
int main(int argc, char **argv)
{
    int w = 0;
//    string name = "forest"; if (w < 10) name += argv[1][0]; else name = name + argv[1][0] + argv[1][1];
  //  freopen((name+".in").c_str(), "w", stdout);
//    freopen((name+".in1").c_str(), "w", stderr);
    srand(time(0));puts("1");
    int n = N[w], Q = N[w]; int m = (n - 1)  / 3; if (!hasL[w]) m = n - 1;
    printf("%d %d %d\n", n, m, Q);
    fprintf(stderr, "%d %d\n", n, Q - (n - 1 - m));
    
    for (int i = 1; i <= n; i++){
        int val = Rand() % 20 + 1;
        printf("%d", val);
        putchar(i == n ? '\n' : ' ');
 //       fprintf(stderr, "%d", val);
 //       fputc((i == n ? '\n' : ' '), stderr);
    }

    
    for (int i = 1; i <= n; i++) uf.f[i] = i;

    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= 1000000; i++) swap(p[Rand() % n + 1], p[Rand() % n + 1]);
    for (int i = 2; i <= n; i++){
        int delta = rand() % 4 + 1;
        if (isChain[w]) delta = 1;
        int a = max(1, i - delta);
        f[i][0] = a; dep[i] = dep[a] + 1;
        edge[++tot] = make_pair(i, a);
        if (rand() & 1) swap(edge[tot].first, edge[tot].second);
    }
    for (int i = 1; i <= 1000000; i++) swap(edge[Rand() % tot + 1], edge[Rand() % tot + 1]);
 //   for (int i = 1; i < n; i++) fprintf(stderr, "%d %d\n", p[edge[i].first], p[edge[i].second]);
    int now = 0;
    for (int i = 1; i <= m; i++){
        printf("%d %d\n", p[edge[now + 1].first], p[edge[now + 1].second]);
        uf.merge(edge[now + 1].first, edge[now + 1].second);
        now++;
    }
    
    for (int x = 1; x <= n; x++)
        for (int i = 1; f[x][i - 1]; i++) f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = 1; i <= Q; i++){
        if (rand() & 1 || now == n - 1){
            int a = Rand() % n + 1, b = Rand() % n + 1;
            while (!uf.same(a, b)){
                a = Rand() % n + 1;
                b = Rand() % n + 1;
            }
            int c = lca(a, b); int dis = dep[a] + dep[b] - dep[c] * 2 + 1;
            int k = Rand() % dis + 1;
            k = min(k, K[w]);
            printf("Q %d %d %d\n", p[a], p[b], k);
  //          fprintf(stderr, "Q %d %d %d\n", p[a], p[b], k);
        }
        else{
            printf("L %d %d\n", p[edge[now + 1].first], p[edge[now + 1].second]);
            uf.merge(edge[now + 1].first, edge[now + 1].second);
            now++;
        }
    }
    
    
}
