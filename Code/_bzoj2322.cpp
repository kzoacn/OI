#include <cstdio>
#include <set>
using namespace std;

typedef long long ll;

#define N 10000
#define M 100000
#define Q 30000
#define LOG 64

struct edge {
	int next, node;
	ll w;
} e[M << 1 | 1];
int head[N + 1], tot = 0;

inline void addedge(int a, int b, ll w) {
	e[++tot].next = head[a];
	head[a] = tot, e[tot].node = b, e[tot].w = w;
}

struct inedge {
	int a, b;
	ll w;
} ie[M + 1];
bool del[M + 1];

int n, m, qc, x, y, q[Q + 1], cnt, ccnt;
ll a[M + 1], w, ans[Q + 1], f[N + 1], chain[N + 1], r[LOG + 1];
bool v[M + 1], vis[N + 1];
set <ll> h;

inline ll eliminate(ll x) {
	for (int k = LOG - 1; k >= 0; --k)
		if (r[k] && ((x >> k) & 1LL)) x ^= r[k];
	return x;
}

inline ll calc() {
	for (int i = 1; i <= cnt; ++i) v[i] = false;
	for (int k = LOG - 1; k >= 0; --k) {
		int p = 0;
		for (int i = 1; !p && i <= cnt; ++i)
			if (!v[i] && ((a[i] >> k) & 1LL)) p = i;
		if (!p) {
			r[k] = 0;
			continue;
		}
		v[p] = true, r[k] = a[p];
		for (int i = 1; i <= cnt; ++i)
			if (i != p && ((a[i] >> k) & 1LL)) a[i] ^= a[p];
	}
	int cur = 0;
	for (int i = 1; i <= cnt; ++i)
		if (a[i]) a[++cur] = a[i];
	cnt = cur;
	
	h.clear(), cur = 0;
	for (int i = 1; i <= ccnt; ++i) {
		ll x = eliminate(chain[i]);
		if (h.find(x) == h.end()) {
			chain[++cur] = chain[i];
			h.insert(x);
		}
	}
	ccnt = cur;
	
	return (ll)ccnt * (1LL << cnt) - 1;
}

void dfs(int x) {
	vis[x] = true;
	for (int i = head[x]; i; i = e[i].next) {
		int node = e[i].node;
		if (vis[node]) a[++cnt] = f[x] ^ f[node] ^ e[i].w;
		else {
			f[node] = f[x] ^ e[i].w;
			chain[++ccnt] = f[node];
			dfs(node);
		}
	}
}

int main(int argc, char* argv[]) {
#ifdef KANARI
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	scanf("%d%d%d", &n, &m, &qc);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%lld", &x, &y, &w);
		ie[i].a = x, ie[i].b = y, ie[i].w = w;
	}
	for (int i = 1; i <= qc; ++i) {
		scanf("%d", q + i);
		del[q[i]] = true;
	}
	
	for (int i = 1; i <= m; ++i)
		if (!del[i]) {
			addedge(ie[i].a, ie[i].b, ie[i].w);
			addedge(ie[i].b, ie[i].a, ie[i].w);
		}
	chain[++ccnt] = 0LL;
	dfs(1);
	
	ans[qc + 1] = calc();
	for (int i = qc; i > 0; --i) {
		x = ie[q[i]].a, y = ie[q[i]].b;
		addedge(x, y, ie[q[i]].w), addedge(y, x, ie[q[i]].w);
		if (vis[x] && vis[y]) a[++cnt] = f[x] ^ f[y] ^ ie[q[i]].w;
		else if (vis[x]) dfs(x);
		else if (vis[y]) dfs(y);
		ans[i] = calc();
	}
	
	for (int i = 1; i <= qc + 1; ++i) printf("%lld\n", ans[i]);
	
	return 0;
}
