#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

ll k;
int n, mid;
const int max_n = (1 << 23) + 10;

inline int getnum() {
	int ans = 0; char c; bool flag = false;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-') flag = true; else ans = c - '0';
	while (isdigit(c = getchar())) ans = ans * 10 + c - '0';
	return ans * (flag ? -1 : 1);
}

int tot;

inline int get_rev(int a, int n) {
	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += (a >> (n - i - 1) & 1) << i;
	return ans;
}

inline int qufan(int a, int n) {
	for (int i = 0; i < n; i++)
		a ^= (1 << i);
	return a;
}

void print(int first, int second, int other) {
	for (int i = mid - 1; i >= 0; i--)
		putchar('0' + (first >> i & 1));
	
	if (n % 2 == 1) {
		putchar('0' + other);
	}

	for (int i = mid - 1; i >= 0; i--)
		putchar('0' + (second >> i & 1));
	putchar('\n');

	exit(0);
}

int main() {
	freopen("str.in", "r", stdin);
	freopen("str.out", "w", stdout);
	cin >> n >> k;
	if (n == 1) {
		cout << -1 << endl;
		return 0;
	} else if (n == 2) {
		if (k == 1) cout << "01" << endl;
		else cout << -1 << endl;
		return 0;
	}

	mid = n / 2;
	tot = (1 << (mid - 1));
	int full_tot = 1 << mid;

	int xs = 1;
	if (n % 2 == 1) xs = 2;

	ll cur_idx = -1;
	for (int i = 0; i < tot; i++) {
		cur_idx += ((tot - i) * xs * 2 - (n % 2 ? 1 : 0));
		if (cur_idx >= k) {
			cur_idx -= (tot - i) * xs * 2 - (n % 2 ? 1 : 0);
			for (int j = 0; j < full_tot; j++) {
				int rev_now = get_rev(j, mid);
				int rev_qf_now = qufan(rev_now, mid);
				if (rev_now >= i && rev_qf_now >= i) {
					cur_idx++;		
					if (cur_idx >= k)
						print(i, j, 0);
				}
			}

			if (n % 2 == 1) {
				for (int j = 0; j < full_tot; j++) {
					int rev_now = get_rev(j, mid);
					int rev_qf_now = qufan(rev_now, mid);
					if (rev_qf_now == i) continue;
					if (rev_now >= i && rev_qf_now >= i) {
						cur_idx++;
						if (cur_idx >= k)
							print(i, j, 1);
					}
				}
			}
		}
	}

	cout << -1 << endl;
}
