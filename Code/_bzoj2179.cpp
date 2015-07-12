#include<bits/stdc++.h>
using namespace std;
typedef complex<double> cp;
const int maxn=1<<18;
const double pi=acos(-1);
int a[maxn],b[maxn],c[maxn];
int n,N;
int main(){
//  freopen("bzoj2194.in","r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int x,y;scanf("%d%d",&x,&y);
        a[i]=x;
        b[i]=y;
    }
    for(int k=0;k<n;k++)
    for(int i=0;i<=k;i++)
    c[k]+=a[i]*b[k-i];
    for(int i=0;i<n;i++)
    printf("%d\n",c[i]);
    return 0;
}
