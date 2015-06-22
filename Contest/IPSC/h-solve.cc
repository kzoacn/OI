#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > G, C;
vector<bool> V;

bool DFS(int x) {
    V[x] = true;
    if (x == 1)
        return true;
    for (int y : G[x])
        if (C[x][y] > 0 && !V[y] && DFS(y)) {
            --C[x][y];
            ++C[y][x];
            return true;
        }
    return false;
}

int main() {
    int t;
    cin >> t;
    for (int ti = 0; ti < t; ++ti) {
        int n, m;
        cin >> n >> m;
        G.clear();
        G.resize(n);
        C.clear();
        C.resize(n, vector<int>(n, 0));
        vector<int> D(n, 0);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            ++D[u];
            ++D[v];
            G[u].push_back(v);
            G[v].push_back(u);
            ++C[u][v];
            ++C[v][u];
        }

        int max_sum = m;
        while (true) {
            V.clear();
            V.resize(n, false);
            if (!DFS(0))
                break;
            --max_sum;
        }

        vector<bool> P(2 * m + 1, false);
        P[0] = true;
        for (int i = 2; i < n; ++i) {
            vector<bool> T(2 * m + 1, false);
            for (int j = 0; j <= 2 * m; ++j)
                if (P[j]) {
                    T[j + D[i]] = true;
                    T[abs(j - D[i])] = true;
                }
            P.swap(T);
        }
        int min_diff = n * n;
        for (int j = 0; j <= 2 * m; ++j)
            if (P[j])
                min_diff = min(min_diff, abs(abs(D[0] - D[1]) - j) / 2);

        cout << max_sum << " " << min_diff << endl;
    }
}
