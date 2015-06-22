#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 1000000007

struct Tree {
  int leaves;
  vector<int> times;
  vector<int> content;

  int lower_bound(int time) {
    return ::lower_bound(times.begin(), times.end(), time) - times.begin();
  }

  void get(int index, int& result) {
    for (int v = leaves + index; v; v /= 2) {
      result = max(result, content[v]);
    }
  }

  void set(int value, int from, int to) {
    set(value, from, to, 1, 0, leaves);
  }

  void set(int value, int from, int to, int v, int vleft, int vright) {
    if (from >= vright || to <= vleft) return;
    if (vleft >= from && vright <= to) {
      content[v] = value;
      return;
    }
    set(value, from, to, v*2, vleft, (vleft+vright)/2);
    set(value, from, to, v*2+1, (vleft+vright)/2, vright);
  }
};

int N, C, Q;
int H, H2, H2L, timenow;
vector<int> parent;
vector<int> height;
vector<int> timeenter;
vector<int> timeexit;
vector<vector<int> > children;
vector<vector<int> > level;
vector<Tree> trees;

void maketrees(int v, int vleft, int vright) {
  Tree& t = trees[v];
  int size = level[vleft].size();
  t.leaves = 1;
  while (t.leaves < size) t.leaves *= 2;
  t.content.resize(t.leaves * 2);
/*
  for (int c : level[vleft]) {
    t.times.push_back(timeexit[c]);
  }*/
  for(int i=0;i<level[vleft].size();i++){
  	t.times.push_back(timeexit[level[vleft][i]]);
  }

  if (vright - vleft > 1) {
    maketrees(v*2, vleft, (vleft+vright)/2);
    maketrees(v*2+1, (vleft+vright)/2, vright);
  }
}

void gset(int eventid, int a, int from, int to, int v, int vleft, int vright) {
  if (from >= vright || to <= vleft) return;
  if (vleft >= from && vright <= to) {
    int li = trees[v].lower_bound(timeenter[a]);
    int ri = trees[v].lower_bound(timeexit[a] + 1);
    trees[v].set(eventid, li, ri);
    return;
  }
  gset(eventid, a, from, to, v*2, vleft, (vleft+vright)/2);
  gset(eventid, a, from, to, v*2+1, (vleft+vright)/2, vright);
}

void traverse(int v) {
  timeenter[v] = timenow++;

  H = max(H, height[v] + 1);
  level[height[v]].push_back(v);

  for (int u=0 ;u< children[v].size();u++) {
    height[children[v][u]] = height[v] + 1;
    traverse(children[v][u]);
  }

  timeexit[v] = timenow++;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int N, C, Q;
    scanf("%d%d%d", &N, &C, &Q);

    parent.clear(); parent.resize(N);
    height.clear(); height.resize(N);
    timeenter.clear(); timeenter.resize(N);
    timeexit.clear(); timeexit.resize(N);
    children.clear(); children.resize(N);
    level.clear(); level.resize(N);
    trees.clear();
    H = H2 = H2L = timenow = 0;

    parent[0] = -1;
    for (int i = 1; i < N; i++) {
      scanf("%d", &parent[i]);
      parent[i]--;
      children[parent[i]].push_back(i);
    }

    traverse(0);

    H2 = 1;
    while (H2 < H) H2 *= 2, H2L++;
    level.resize(H2);
    trees.resize(H2 * 2);

    maketrees(1, 0, H2);

    vector<int> colors(Q + 1);
    colors[0] = 1;

    long long R = 0;

    for (int eventid = 1; eventid <= Q; eventid++) {
      int a, l, c;
      scanf("%d%d%d", &a, &l, &c);
      a--;

      if (c) {
        colors[eventid] = c;
        int from = height[a], to = min(height[a] + l + 1, H);
        gset(eventid, a, from, to, 1, 0, H2);
      } else {
        int mtime = 0;

        for (int v = H2 + height[a]; v; v /= 2) {
          int pos = trees[v].lower_bound(timeexit[a]);
          trees[v].get(pos, mtime);
        }

        R += 1LL * colors[mtime] * eventid;
        R %= MOD;
      }
    }

    printf("%lld\n", R);
  }
}
