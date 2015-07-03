#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,m,q;
int fa[maxn],len[maxn];
void init(){for(int i=1;i<=n;i++)fa[i]=i;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
int vis[maxn];
int C;
vector<int>G[maxn];
int cir(int s){
	int c=++C;
	static int d[maxn];
	int A=0;
	queue<int>q;q.push(s);
	vis[s]=c;d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v]==c)continue;
			vis[v]=c;
			d[v]=d[u]+1;
			q.push(v);
			if(d[v]>d[A])A=v;
		}
	}
	c=++C;
	q.push(A);
	vis[A]=c;d[A]=0;
	int ans=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v]==c)continue;
			vis[v]=c;
			d[v]=d[u]+1;
			q.push(v);
			ans=max(ans,d[v]);
		}
	}
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)fa[i]=i;
	while(m--){
		int u,v;scanf("%d%d",&u,&v);
		merge(u,v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		len[find(i)]=cir(i);
	}	
	while(q--){
		int ty;scanf("%d",&ty);
		if(ty==1){
			int x;scanf("%d",&x);
			printf("%d\n",len[find(x)]);
		}else{
			int x,y;scanf("%d%d",&x,&y);
			x=find(x);y=find(y);
			if(x==y)continue;
			fa[x]=y;
			len[y]=max(max(len[y],len[x]),(len[x]+1)/2+1+(len[y]+1)/2);
		}
	}
	return 0;
}
