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
const int mod = 10007;
const int max_n = 1010;

int sum[max_n][max_n], n;

inline int getnum() {
	int ans = 0; char c; bool flag = false;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-') flag = true; else ans = c - '0';
	while (isdigit(c = getchar())) ans = ans * 10 + c - '0';
	return ans * (flag ? -1 : 1);
}

inline char getmychar() {
	char c;
	while (!isalpha(c = getchar()));
	return c;
}

inline bool legal(int x1, int y1, int x2, int y2) {
	int _ = sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
	return _ == (x2 - x1 + 1) * (y2 - y1 + 1);
}

inline void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

inline void sub(int &a, int b) {
	a = (a + mod - b) % mod;
}

bool inter(int x1, int y1, int x2, int y2, int a1, int b1, int a2, int b2) {
	return max(x1, a1) <= min(x2, a2) && max(y1, b1) <= min(y2, b2);
}	

int main() {
	freopen("rect.in", "r", stdin);
	freopen("rect.out", "w", stdout);
	n = getnum();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			char c = getmychar();
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
			if (c == 'C')
				sum[i][j]++;
		}

	ll ans = 0;

	for (int x1 = 1; x1 <= n; x1++)
		for (int y1 = 1; y1 <= n; y1++)
			for (int x2 = x1; x2 <= n; x2++)
				for (int y2 = y1; y2 <= n; y2++) {
					if (!legal(x1, y1, x2, y2)) continue;
					if (x1 == x2 && y1 == y2) continue;
					for (int a1 = 1; a1 <= n; a1++)
						for (int b1 = 1; b1 <= n; b1++)
							for (int a2 = a1; a2 <= n; a2++)
								for (int b2 = b1; b2 <= n; b2++) {
									if (!legal(a1, b1, a2, b2))
										continue;
									if (a1 == a2 && b1 == b2) continue;
									if (inter(x1, y1, x2, y2, a1, b1, a2, b2)) continue;
									ans++;			
								}
				}
	ans /= 2;	
	ans %= mod;
	cout << ans << endl;
}
