#include <cstdio>
#include <algorithm>
#include <queue>
#define mp make_pair
#define X first
#define Y second
using namespace std;
const int N=1000100;
priority_queue<pair<int,int> > q;
int n,k,st,ed,p[N],b[N];
bool ok;
void print(int n) {
    for (int i=0;i<n;i++) printf("%d ",p[i]);
    printf("%d\n",p[n]);
}
int main() {
    int i,x,x1,x2,y1,y2;
    scanf("%d%d%d",&k,&st,&ed);
    for (i=1;i<=k;i++) {
        scanf("%d",&b[i]);
        n+=b[i];
    } b[st]--; b[ed]--;
    n--; p[0]=st; p[n]=ed;
    if (!n) {
        if (st!=ed) return puts("0"),0;
        else return printf("%d\n",st),0;
    }
    for (i=1;i<=k;i++) if (b[i]>0) q.push(mp(b[i],i));
    for (i=1;i<n;i++) {
        x1=q.top().X;
        y1=q.top().Y;
        q.pop();
        if (y1!=p[i-1]) {
            p[i]=y1;
            if (x1>1) q.push(mp(x1-1,y1));
        } else {
            if (q.empty()) return puts("0"),0;
            x2=q.top().X;
            y2=q.top().Y;
            q.pop();
            p[i]=y2;
            q.push(mp(x1,y1));
            if (x2>1) q.push(mp(x2-1,y2));
        }
    }
    if (!q.empty()) return puts("0"),0;
    if (p[n-1]!=p[n]) print(n);
    else {
        if (p[n-3]!=p[n-1]) {
            swap(p[n-2],p[n-1]);
            print(n);
        } else return puts("0"),0;
    }
    return 0;
}
