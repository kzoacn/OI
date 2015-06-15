#include<bits/stdc++.h>
using namespace std;
const int maxn=150010;
typedef pair<int,int> pii;
typedef long long LL;
int n,m,L,lef,rig,col[maxn];
LL lans;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
vector<pii>G[maxn];
LL ans=0;
void dfs(int x,int fa=0,int d=0){
	if(lef<=col[x]&&col[x]<=rig)ans+=d;
	for(int i=0;i<G[x].size();i++){
		pii e=G[x][i];
		if(e.first==fa)continue;
		dfs(e.first,x,d+e.second);
	}
}
int main(){
	n=getint();m=getint();L=getint();
	for(int i=1;i<=n;i++)col[i]=getint();
	for(int i=1;i<n;i++){
		int u=getint(),v=getint(),w=getint();
		G[u].push_back(pii(v,w));
		G[v].push_back(pii(u,w));
	}while(m--){
		int x=getint();
		int a=getint(),b=getint();
		lef=min((a+lans)%L,(b+lans)%L);
		rig=max((a+lans)%L,(b+lans)%L);
		dfs(x);
		printf("%lld\n",lans=ans);ans=0;
	}
	return 0;
}
