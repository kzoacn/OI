#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+4;
typedef long long LL;
LL d[maxn],f[maxn],fa[maxn];
vector<int>G[maxn];
LL sum=0;
int a[maxn];
LL lcm(LL a,LL b){return a/__gcd(a,b)*b;}
void duang(){cout<<sum<<endl;exit(0);}
void dfs(int u){
	d[u]=1;f[u]=a[u];
	if(a[u])return;
	f[u]=sum;
	int son=0;
	for(int v:G[u]){
		if(v==fa[u])continue;
		son++;
		fa[v]=u;
		dfs(v);
		f[u]=min(f[u],f[v]);
		if(d[u]>sum/d[v])duang();
		d[u]=lcm(d[u],d[v]);
	}
	f[u]=f[u]/d[u]*d[u]*son;
	d[u]=d[u]*son;
	if(d[u]>sum)duang();
}
int n,m;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	cout<<sum-f[1]<<endl;
	return 0;
}
