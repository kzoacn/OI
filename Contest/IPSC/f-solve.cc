#include <cstdio>
#include <vector>
#include <map>
using namespace std;

#define MOD 1000000007

int main() {
freopen("f1.in","r",stdin);
  int T;
  scanf("%d", &T);
  while (T--) {
    int N, Q;
    scanf("%d%d", &N, &Q);

    long long R = 0, F = 0;

    vector<int> parent[2];
    for (int t = 0; t < 2; t++) for (int i = 0; i < N; i++) parent[t].push_back(i);

    vector<vector<int> > members[2];
    members[0].resize(N);
    members[1].resize(N);
    for (int t = 0; t < 2; t++) for (int i = 0; i < N; i++) members[t][i].push_back(i);

    map<pair<int,int>,int> count;   // a hashmap would be faster...
    for (int i = 0; i < N; i++) count[make_pair(i, i)] = 1;

    for (int qi = 1; qi <= Q; qi++) {
      int t, a, b;
      scanf("%d%d%d", &t, &a, &b);
      t--; a--; b--;

      a = parent[t][a]; b = parent[t][b];

      if (a != b) {
        if (members[t][a].size() < members[t][b].size()) swap(a, b);

        for (int i=0 ; i<members[t][b].size();i++) {
        	int c=members[t][b][i];
          pair<int,int> old = make_pair(parent[0][c], parent[1][c]);
          count[old]--;
          if (count[old] == 0) count.erase(old);
          parent[t][c] = a;
          members[t][a].push_back(c);
          R += count[make_pair(parent[0][c], parent[1][c])];
        }
        for (int i=0 ;i< members[t][b].size();i++) {
        int c=members[t][b][i];
          count[make_pair(parent[0][c], parent[1][c])]++;
        }
        members[t][b].clear();
      }

      F += (R % MOD) * qi;
      F %= MOD;
    }

    printf("%lld\n", F);
  }
}
