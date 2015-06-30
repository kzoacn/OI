#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
map<pair<int,int>,int>M;
int a[maxn],n,m;
int Q(int x,int l,int ty){
	if(x==1&&ty==-1)ty=1;
	if(x==n&&ty==1)ty=-1;
	if(ty==1){
		int nx=upper_bound(a+1,a+1+n,a[x]+l)-a-1;
		if(x==nx)return x;
		int d=a[nx]-a[x];
		return Q(nx,l-(a[nx]-a[x]),-ty);
	}else{
		int nx=lower_bound(a+1,a+1+n,a[x]-l)-a;
		if(x==nx)return x;
		return Q(nx,l-(a[x]-a[nx]),-ty);
	}
}
int ord[maxn],mp[maxn];
bool cmp(int x,int y){return a[x]<a[y];}
int main(){
	scanf("%d%d",&n,&m);
	if(n==1){while(m--)puts("1");return 0;}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),ord[i]=i;
	sort(ord+1,ord+1+n,cmp);
	for(int i=1;i<=n;i++)mp[ord[i]]=i;
	sort(a+1,a+1+n);
	while(m--){
		M.clear();
		int x,l;scanf("%d%d",&x,&l);
		x=mp[x];
		printf("%d\n",ord[Q(x,l,1)]);
	}
	return 0;
}
