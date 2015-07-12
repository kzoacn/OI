#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e6+5;
int n,m;
int a[maxn],b[maxn];
void sol(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)scanf("%d",&b[i]);
    sort(a+1,a+1+n,greater<int>());
    sort(b+1,b+1+m,greater<int>());
    long long ans=0;
    for(int i=1;i<=min(n,m);i++){
        if(a[i]>b[i])ans+=a[i]-b[i];
    }cout<<ans<<endl;
}
int main(){
	freopen("B.in","r",stdin);
    int T;scanf("%d",&T);
    while(T--)sol();
    return 0;
}
