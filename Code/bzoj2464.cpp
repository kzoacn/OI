#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
int n,m;
int s,t;
int mp[501][501],tot,a[501][501];
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
typedef pair<int,int> par;
vector<par>G[250010];
void add(int u,int v,int w){
//	cerr<<u<<" "<<v<<" "<<w<<endl;
	G[u].push_back(par(v,w));
//	G[v].push_back(par(u,w));
}
typedef __gnu_pbds::priority_queue<par,greater<par>,__gnu_pbds::pairing_heap_tag> Heap;
typedef Heap::point_iterator iter;
iter d[250010];
Heap q;
int dijk(){
	static int vis[250010];
	memset(vis,0,sizeof vis);q.clear();
	for(int i=1;i<=tot;i++)d[i]=q.end();
	vis[s]=1;d[s]=q.push(par(0,s));
	while(!q.empty()){
		int u=q.top().second;vis[u]=1;
		if(u==t)return d[t]->first;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].first,w=G[u][i].second;
			if(d[v]==q.end())d[v]=q.push(par(1e9,v));
			if(!vis[v]&&d[v]->first>d[u]->first+w)
				q.modify(d[v],par(d[u]->first+w,v));
		}q.erase(d[u]);
	}
}
int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		if(!n)break;
		tot=0;
		for(int i=1;i<=n;i++){
			static char str[501];
			scanf("%s",str+1);
			for(int j=1;j<=m;j++)
				mp[i][j]=++tot,
				a[i][j]=str[j]=='#',
				G[tot].clear();
		}
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
			for(int k=0;k<4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x<1||x>n||y<1||y>m)continue;
				add(mp[i][j],mp[x][y],a[x][y]^a[i][j]);
			}
		}int x,y;scanf("%d%d",&x,&y);s=mp[x+1][y+1];
		scanf("%d%d",&x,&y);t=mp[x+1][y+1];
		printf("%d\n",dijk());
	}
	return 0;
}
