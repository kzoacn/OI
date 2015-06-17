#include<bits/stdc++.h>
using namespace std;
const int maxn=10010;
int n,m;
struct edge{int u,v,w;};
vector<edge>G[maxn];
void add(int u,int v,int w){
//	cerr<<u<<" "<<v<<" "<<w<<endl;
	G[u].push_back((edge){u,v,w});
}
void spfa(){
	static int vis[maxn],d[maxn],in[maxn];
	for(int i=1;i<=n;i++)d[i]=INT_MAX;
	d[0]=0;
	queue<int>q;q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		if(in[u]>5)break;
		for(int i=0;i<G[u].size();i++){
			edge e=G[u][i];
			if(d[e.v]>d[u]+e.w){
				d[e.v]=d[u]+e.w;
				if(!vis[e.v])vis[e.v]=1,q.push(e.v),in[e.v]++;
			}
		}
	}if(*max_element(in+1,in+1+n)<5)
		puts("Yes");
	else puts("No");
}
int main(){
	freopen("bzoj3436.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)add(0,i,0);
	while(m--){
		int ty,u,v,w;scanf("%d",&ty);
		scanf("%d%d",&u,&v);
		if(ty==1){
			scanf("%d",&w);
			add(u,v,-w);
		}else if(ty==2){
			scanf("%d",&w);
			add(v,u,w);
		}else{
			add(u,v,0);
			add(v,u,0);
		}
	}spfa();
	return 0;
}
