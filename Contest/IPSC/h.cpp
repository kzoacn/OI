#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int max_n = 210;
const int max_m = max_n * max_n;
const int inf = 1e9;

inline int getnum() {
	int ans = 0; char c; bool flag = false;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-') flag = true; else ans = c - '0';
	while (isdigit(c = getchar())) ans = ans * 10 + c - '0';
	return ans * (flag ? -1 : 1);
}

int n, m;

namespace isap {
	int point[max_n], nxt[max_m], v[max_m], remain[max_m], tot;
	int last_edge[max_n], cur[max_n], deep[max_n], num[max_n];

	inline void clear() {
		memset(point, -1, sizeof(point));
		tot = -1;
	}
	
	inline void add_edge(int x, int y, int cap) {
		tot++; nxt[tot] = point[x]; point[x] = tot; v[tot] = y; remain[tot] = cap;
		tot++; nxt[tot] = point[y]; point[y] = tot; v[tot] = x; remain[tot] = cap;
	}

	inline int add_flow(int s, int t) {
		int ans = inf, now = t;
		while (now != s) {
			ans = min(ans, remain[last_edge[now]]);
			now = v[last_edge[now] ^ 1];
		}
		now = t;
		while (now != s) {
			remain[last_edge[now]] -= ans;
			remain[last_edge[now] ^ 1] += ans;
			now = v[last_edge[now] ^ 1];
		}
		return ans;
	}

	inline void bfs(int t) {
		num[0] = 0;
		for (int i = 1; i <= n; i++)
			deep[i] = n, num[i] = 0;
		queue<int> q;	
		q.push(t); deep[t] = 0;
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int tmp = point[now], u; u = v[tmp], tmp != -1; tmp = nxt[tmp])
				if (remain[tmp ^ 1] && deep[u] == n) {
					deep[u] = deep[now] + 1;
					q.push(u);
				}
		}
		for (int i = 1; i <= n; i++)
			num[deep[i]]++;
	}

	inline int isap(int s, int t) {
		int ans = 0, now = s;
		for (int i = 1; i <= n; i++)
			cur[i] = point[i];
		bfs(t);

		while (deep[s] < n) {
			if (now == t) {
				ans += add_flow(s, t);
				now = s;
			}
			bool isok = false;
			for (int tmp = cur[now], u; u = v[tmp], tmp != -1; tmp = nxt[tmp])
				if (remain[tmp] && deep[u] + 1 == deep[now]) {
					isok = true;
					last_edge[u] = tmp;
					cur[now] = tmp;
					now = u;
					break;
				}
			if (!isok) {
				int minn = n - 1;
				for (int tmp = point[now], u; u = v[tmp], tmp != -1; tmp = nxt[tmp])
					if (remain[tmp])
						minn = min(minn, deep[u]);
				if (!(--num[deep[now]])) break;
				num[deep[now] = minn + 1]++;
				cur[now] = point[now];
				if (now != s)
					now = v[last_edge[now] ^ 1];
			}
		}
		return ans;
	}
}

namespace dp {
	int deg[max_n], deg_sum;
	int f[max_m * 2];

	inline void clear() {
		memset(deg, 0, sizeof(deg));
		memset(f, 0, sizeof(f));
		deg_sum = 0;
	}

	inline int solve() {
		f[deg[1]] = 1;	
		for (int i = 3; i <= n; i++) {
			int low_tar = deg[1] + deg[i];
			int v = deg[i];
			for (int j = deg_sum; j >= low_tar; j--)
				f[j] |= f[j - v];
		}
		int min_dif = deg_sum;
		int mid = deg_sum >> 1;
		for (int i = deg[1]; i <= deg_sum; i++)
			if (f[i] && abs(i - mid) < min_dif)
				min_dif = abs(i - mid);
		return min_dif;
	}
}

inline void solve() {
	isap::clear();	
	dp::clear();

	n = getnum(); m = getnum();
	for (int i = 1; i <= m; i++) {
		int x = getnum();
		int y = getnum();
		isap::add_edge(x, y, 1);
		dp::deg[x]++;
		dp::deg[y]++;
		dp::deg_sum += 2;
	}

	printf("%d ", m - isap::isap(1, 2));
	printf("%d\n", dp::solve());
}

int main() {
	freopen("h2.in","r",stdin);
	int t = getnum();
	while (t--) {
		solve();
	}
}
