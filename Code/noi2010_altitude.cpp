#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
const int maxn=505;
typedef pair<int,int> par;
vector<par>G[maxn*maxn];
void add(int u,int v,int w){
//	fprintf(stderr,"%d->%d w:%d\n",u,v,w);
	G[u].push_back(par(v,w));
}
int s=1,t,n,mp[maxn][maxn];
typedef __gnu_pbds::priority_queue<par,greater<par>,__gnu_pbds::pairing_heap_tag> Heap;
typedef Heap::point_iterator iter;
iter d[maxn*maxn];
int dijk(){
	static int vis[maxn*maxn];
	Heap q;
	for(int i=1;i<=(n+1)*(n+1);i++)d[i]=q.end();
	d[1]=q.push(par(0,1));vis[1]=1;
	while(!q.empty()){
		int u=q.top().second;vis[u]=1;
		if(u==t)return d[t]->first;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].first,w=G[u][i].second;
			if(vis[v])continue;
			if(d[v]==q.end())d[v]=q.push(par(INT_MAX,v));
			if(d[v]->first>d[u]->first+w)
				q.modify(d[v],par(d[u]->first+w,v));
		}q.erase(d[u]);d[u]=q.end();
	}
}
int getint(){
	char c=getchar();int res=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int main(){
	scanf("%d",&n);
	int tot=0;
	for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)
	mp[i][j]=++tot;t=tot;
	for(int i=1;i<=n+1;i++)for(int j=1;j<=n;j++)
	add(mp[i][j],mp[i-1][j],getint());
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)
	add(mp[i][j-1],mp[i][j],getint());
	for(int i=1;i<=n+1;i++)for(int j=1;j<=n;j++)
	add(mp[i-1][j],mp[i][j],getint());
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)
	add(mp[i][j],mp[i][j-1],getint());
	for(int i=1;i<=n;i++)add(s,mp[i][0],0),add(s,mp[n+1][i],0);
	for(int i=1;i<=n;i++)add(mp[i][n+1],t,0),add(mp[0][i],t,0);
	cout<<dijk()<<endl;
	return 0;
}
