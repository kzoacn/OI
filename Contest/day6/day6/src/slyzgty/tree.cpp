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

const int max_n = 5e4 + 10;
const int max_n2 = 1e5 + 10;

int n;

int color[max_n][2], value[max_n][2];

inline int getnum() {
	int ans = 0; char c; bool flag = false;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-') flag = true; else ans = c - '0';
	while (isdigit(c = getchar())) ans = ans * 10 + c - '0';
	return ans * (flag ? -1 : 1);
}

namespace seg {
	const int max_node = max_n * 4;

	struct seg_data {
		int sum[2][2], dis[2][2];
		int white_sum[2][2], white_dis[2][2];
		int color_cover;
		seg_data() {
			color_cover = -1;
		}
		void single(int idx) {
			white_sum[0][0] = value[idx][0];
			white_sum[1][1] = value[idx][1];
			white_sum[0][1] = white_sum[1][0] = value[idx][0] + value[idx][1];
			
			white_dis[0][0] = white_dis[1][1] = 1;
			white_dis[0][1] = white_dis[1][0] = 2;
			
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (!color[idx][i] && !color[idx][j]) {
						sum[i][j] = white_sum[i][j];
						dis[i][j] = white_dis[i][j];
					} else {
						sum[i][j] = -1;
						dis[i][j] = -1;
					}
		}
		void rev() {
			swap(sum[0][1], sum[1][0]);
			swap(dis[0][1], dis[1][0]);
			swap(white_sum[0][1], white_sum[1][0]);
			swap(white_dis[0][1], white_dis[1][0]);
		}
		void set_color(int c, int l, int r) {
			color_cover = c;
			if (!c) {
				memcpy(sum, white_sum, sizeof(white_sum));
				memcpy(dis, white_dis, sizeof(white_dis));
			} else {
				memset(sum, -1, sizeof(sum));
				memset(dis, -1, sizeof(dis));
			}

			if (l == r) {
				color[l][0] = color[l][1] = c;
			}
		}
		void update(seg_data a, seg_data b) {
			memset(sum, -1, sizeof(sum));
			memset(dis, -1, sizeof(dis));
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++) {
					int &cur_sum = sum[i][j];
					int &cur_dis = dis[i][j];
					for (int k = 0; k < 2; k++) {
						if (a.sum[i][k] != -1 && b.sum[k][j] != -1) {
							int tmp_sum = a.sum[i][k] + b.sum[k][j];
							int tmp_dis = a.dis[i][k] + b.dis[k][j];
							if (tmp_sum > cur_sum || (tmp_sum == cur_sum && tmp_dis > cur_dis)) {
								cur_sum = tmp_sum;
								cur_dis = tmp_dis;
							}	
						}
					}
				}

			memset(white_sum, -1, sizeof(white_sum));
			memset(white_dis, -1, sizeof(white_dis));
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++) {
					int &cur_sum = white_sum[i][j];
					int &cur_dis = white_dis[i][j];
					for (int k = 0; k < 2; k++)
						if (a.white_sum[i][k] != -1 && b.white_sum[k][j] != -1) {
							int tmp_sum = a.white_sum[i][k] + b.white_sum[k][j];
							int tmp_dis = a.white_dis[i][k] + b.white_dis[k][j];
							if (tmp_sum > cur_sum || (tmp_sum == cur_sum && tmp_dis > cur_dis)) {
								cur_sum = tmp_sum;
								cur_dis = tmp_dis;
							}
						}
				}
		}
		
	} seg[max_node];

	void build(int now, int l, int r) {
		seg_data &cur_node = seg[now];
		if (l == r) {
			color[l][0] = color[l][1] = 0;
			value[l][0] = value[l][1] = 1;
			cur_node.single(l);	
			return;
		}
		int mid = (l + r) >> 1;
		build(now << 1, l, mid);
		build((now << 1) + 1, mid + 1, r);
		cur_node.update(seg[now << 1], seg[(now << 1) + 1]);
	}

	inline void pushdown(int now, int l, int r) {
		if (seg[now].color_cover != -1) {
			int mid = (l + r) >> 1;
			seg[now << 1].set_color(seg[now].color_cover, l, mid);
			seg[(now << 1) + 1].set_color(seg[now].color_cover, mid + 1, r);
			seg[now].color_cover = -1;
		}
	}

	void cover(int now, int l, int r, int lrange, int rrange, int color) {
		seg_data &cur_node = seg[now];
		if (lrange <= l && r <= rrange) {
			cur_node.set_color(color, l, r);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(now, l, r);
		if (lrange <= mid) cover(now << 1, l, mid, lrange, rrange, color);
		if (rrange > mid) cover((now << 1) + 1, mid + 1, r, lrange, rrange, color);
		cur_node.update(seg[now << 1], seg[(now << 1) + 1]);
	}

	void change_color(int now, int l, int r, int x, int layout, int c) {
		if (l == r) {
			color[l][layout] = c;
			seg[now].single(l);
			return;
		}
		pushdown(now, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid)
			change_color(now << 1, l, mid, x, layout, c);
		else
			change_color((now << 1) + 1, mid + 1, r, x, layout, c);
		seg[now].update(seg[now << 1], seg[(now << 1) + 1]);
	}

	void change_value(int now, int l, int r, int x, int layout, int v) {
		if (l == r) {
			value[l][layout] = v;
			seg[now].single(l);
			return;
		}
		pushdown(now, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid) change_value(now << 1, l, mid, x, layout, v);
		else change_value((now << 1) + 1, mid + 1, r, x, layout, v);
		seg[now].update(seg[now << 1], seg[(now << 1) + 1]);
	}

	seg_data query(int now, int l, int r, int lrange, int rrange) {
		if (lrange <= l && r <= rrange)
			return seg[now];
		pushdown(now, l, r);
		int mid = (l + r) >> 1;
		if (rrange <= mid) return query(now << 1, l, mid, lrange, rrange);
		else if (lrange > mid) return query((now << 1) + 1, mid + 1, r, lrange, rrange);
		else {
			seg_data l_ans = query(now << 1, l, mid, lrange, rrange);
			seg_data r_ans = query((now << 1) + 1, mid + 1, r, lrange, rrange);
			seg_data ans;
			ans.update(l_ans, r_ans);
			return ans;
		}
	}
}

namespace tree {
	int point[max_n], nxt[max_n2], v[max_n2], tot;
	int fa[max_n], dep[max_n], size[max_n], fatson[max_n];
	int seq[max_n], dy_seq[max_n], tot_seq, up[max_n];
	
	void dfs(int now) {
		dep[now] = dep[fa[now]] + 1;
		size[now] = 1;
		for (int tmp = point[now], u; u = v[tmp], tmp; tmp = nxt[tmp])
			if (u != fa[now]) {
				fa[u] = now;
				dfs(u);
				size[now] += size[u];
				if (size[u] > size[fatson[now]])
					fatson[now] = u;
			}
	}

	void dfs2(int now) {
		seq[++tot_seq] = now;
		dy_seq[now] = tot_seq;

		if (fatson[now]) {
			up[fatson[now]] = up[now];
			dfs2(fatson[now]);
		}

		for (int tmp = point[now], u; u = v[tmp], tmp; tmp = nxt[tmp])
			if (u != fa[now] && u != fatson[now]) {
				up[u] = u;
				dfs2(u);
			}
	}

	inline void add_edge(int x, int y) {
		tot++; nxt[tot] = point[x]; point[x] = tot; v[tot] = y;
		tot++; nxt[tot] = point[y]; point[y] = tot; v[tot] = x;
	}

	inline void init_tree() {
		for (int i = 1; i < n; i++) {
			int x = getnum();
			int y = getnum();
			add_edge(x, y);
		}

		dfs(1);
		up[1] = 1;
		dfs2(1);
	}
	
	inline void change(int x, int y, int c) {
		while (up[x] != up[y]) {
			if (dep[up[x]] < dep[up[y]]) swap(x, y);
			seg::cover(1, 1, n, dy_seq[up[x]], dy_seq[x], c);
			x = fa[up[x]];
		}
		if (dep[x] < dep[y]) swap(x, y);
		seg::cover(1, 1, n, dy_seq[y], dy_seq[x], c);
	}

	inline pair<int, int> query(int x, int y) {
		seg::seg_data ans_x, ans_y;
		bool use_x = false, use_y = false;

		while (up[x] != up[y]) {
			if (dep[up[x]] > dep[up[y]]) {
				seg::seg_data tmp = seg::query(1, 1, n, dy_seq[up[x]], dy_seq[x]);
				if (!use_x)
					ans_x = tmp;
				else
					ans_x.update(tmp, ans_x);
				use_x = true;
				x = fa[up[x]];
			} else {
				seg::seg_data tmp = seg::query(1, 1, n, dy_seq[up[y]], dy_seq[y]);
				if (!use_y)
					ans_y = tmp;
				else
					ans_y.update(tmp, ans_y);
				use_y = true;
				y = fa[up[y]];
			}
		}

		seg::seg_data tmp;
		if (dep[x] > dep[y]) {
			tmp = seg::query(1, 1, n, dy_seq[y], dy_seq[x]);
			if (use_y) {
				ans_y.rev();
				tmp.update(ans_y, tmp);
			}
			if (use_x)
				tmp.update(tmp, ans_x);
		} else {
			tmp = seg::query(1, 1, n, dy_seq[x], dy_seq[y]);
			if (use_x) {
				ans_x.rev();
				tmp.update(ans_x, tmp);
			}
			if (use_y)
				tmp.update(tmp, ans_y);
		}

		int max_value = -1, max_dis = -1;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				if (tmp.sum[i][j] > max_value || (tmp.sum[i][j] == max_value && tmp.dis[i][j] > max_dis)) {
					max_value = tmp.sum[i][j];
					max_dis = tmp.dis[i][j];
				}
		return make_pair(max_value, max_dis);
	}
}

inline void init() {
	tree::init_tree();
	seg::build(1, 1, n);
}

inline int get_op() {
	char s[20];
	char c;
	int len = 0;
	while (!isalpha(c = getchar()));
	s[len++] = c;
	while (isalpha(c = getchar()))
		s[len++] = c;
	s[len] = '\0';

	if (!strcmp(s, "Cover")) return 1;
	else if (!strcmp(s, "CVal")) return 2;
	else if (!strcmp(s, "CColor")) return 3;
	else if (!strcmp(s, "QMax")) return 4;
	else return 5;
}

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	n = getnum();
	init();

	int Q = getnum();
	while (Q--) {			
		int op = get_op();
		if (op == 1) {
			int s, t, c;
			s = getnum(); t = getnum(); c = getnum();
			tree::change(s, t, c);
		} else if (op == 3) {
			int idx, layer, c;
			idx = getnum(); layer = getnum(); c = getnum();
			seg::change_color(1, 1, n, tree::dy_seq[idx], layer, c);
		} else if (op == 2) {
			int idx, layer, v;
			idx = getnum(); layer = getnum(); v = getnum();
			seg::change_value(1, 1, n, tree::dy_seq[idx], layer, v);
		} else if (op == 4) {
			int s, t;
			s = getnum(); t = getnum();
			pair<int, int> ans = tree::query(s, t);
			printf("%d\n", ans.first);
		} else {
			int s, t;
			s = getnum(); t = getnum();
			pair<int, int> ans = tree::query(s, t);
			printf("%d\n", ans.second);
		}
	}
}
