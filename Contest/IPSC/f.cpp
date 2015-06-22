#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;
const int max_n = 1e6 + 10;
const int mod = 1e9 + 7;

inline int getnum() {
	int ans = 0; char c; bool flag = false;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-') flag = true; else ans = c - '0';
	while (isdigit(c = getchar())) ans = ans * 10 + c - '0';
	return ans * (flag ? -1 : 1);
}

typedef pair<int, int> info;

inline void update(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

map<info, int> cnt;
vector<int> hus[max_n], wife[max_n];
int n, q, hus_idx[max_n], wife_idx[max_n];

inline void solve() {
	n = getnum();
	q = getnum();

	cnt.clear();

	for (int i = 1; i <= n; i++) {
		hus[i].clear();
		wife[i].clear();

		hus[i].push_back(i);
		wife[i].push_back(i);

		hus_idx[i] = i;
		wife_idx[i] = i;
		
		cnt[make_pair(i, i)] = 1;
	}

	int ans = 0, cur_ans = 0;

	for (int t = 1; t <= q; t++) {
		int type = getnum();
		int x = getnum();
		int y = getnum();

		if (type == 1) {
			int fx = hus_idx[x];
			int fy = hus_idx[y];
			if (fx != fy) {
				if (hus[fx].size() > hus[fy].size())
					swap(fx, fy), swap(x, y);
				vector<int> &_ = hus[fx];
				vector<int> &__ = hus[fy];
				for (int i = 0; i < (int)_.size(); i++) {
					int now = _[i];
					info cur = make_pair(fx, wife_idx[now]);	
					info nxt = make_pair(fy, wife_idx[now]);
					if (cnt.count(cur)) {
						int cur_value = cnt[cur];
						if (cnt.count(nxt)) {
							int nxt_value = cnt[nxt];
							update(cur_ans, (ll)cur_value * nxt_value % mod); 
							cnt[nxt] += cur_value;	
						} else {
							cnt[nxt] = cur_value;
						}
						cnt.erase(cur);
					}
					__.push_back(now);	
					hus_idx[now] = fy;
				}
				_.clear();
			}
		} else {
			int fx = wife_idx[x];
			int fy = wife_idx[y];
			if (fx != fy) {
				if (wife[fx].size() > wife[fy].size())
					swap(fx, fy), swap(x, y);
				vector<int> &_ = wife[fx];
				vector<int> &__ = wife[fy];
				for (int i = 0; i < (int)_.size(); i++) {
					int now = _[i];
					info cur = make_pair(hus_idx[now], fx);	
					info nxt = make_pair(hus_idx[now], fy);
					if (cnt.count(cur)) {
						int cur_value = cnt[cur];
						if (cnt.count(nxt)) {
							int nxt_value = cnt[nxt];
							update(cur_ans, (ll)cur_value * nxt_value % mod); 
							cnt[nxt] += cur_value;	
						} else {
							cnt[nxt] = cur_value;
						}
						cnt.erase(cur);
					}
					wife_idx[now] = fy;
					__.push_back(now);	
				}
				_.clear();
			}
		}

		update(ans, (ll)t * cur_ans % mod);
	}

	printf("%d\n", ans);
}

int main() {
	//freopen("input.txt", "r", stdin);
	int t = getnum();
	while (t--) {
		solve();
	}
}
