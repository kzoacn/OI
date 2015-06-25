#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+5;
int getn(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int n,m;
int lin[maxn];
vector<int>G[maxn],Ge[maxn];
int d[maxn];
bool bfs(){
	memset(d,0,sizeof d);		
	queue<int>q;
	for(int i=1;i<=n;i++)if(!lin[i])q.push(i);
	int f=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(u>n){
			int v=lin[u];
			q.push(v);d[v]=d[u]+1;
		}else for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(d[v])continue;
			d[v]=d[u]+1;
			if(lin[v])q.push(v);
			else f=1;
		}
	}return f;
}
int find(int u){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(d[u]+1!=d[v])continue;
		d[v]=-1;
		if(!lin[v]||find(lin[v])){
			lin[v]=u;lin[u]=v;return 1;
		}
	}return 0;
}
int dfn[maxn],low[maxn],bel[maxn],z,B,ins[maxn];
stack<int>S;
void tarjan(int u){
	low[u]=dfn[u]=++z;ins[u]=1;S.push(u);
	for(int i=0;i<Ge[u].size();i++){
		int v=Ge[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v])low[u]=min(low[u],dfn[v]);
	}if(low[u]==dfn[u]){
		int v;B++;
		do{
			v=S.top();S.pop();ins[v]=0;
			bel[v]=B;
		}while(u!=v);
	}
}
pair<int,int> Q[int(6e5+5)];
int main(){
	n=getn();m=getn();
	for(int i=1;i<=m;i++){
		int u=getn(),v=getn();
		Q[i].first=u;
		Q[i].second=v+n;
		G[u].push_back(v+n);
	}while(bfs())
		for(int i=1;i<=n;i++)if(!lin[i])
			find(i);
	for(int i=1;i<=n*2;i++)for(int j=0;j<G[i].size();j++){
		int u=i,v=G[i][j];
		if(lin[u]==v)Ge[v].push_back(u);
		else Ge[u].push_back(v);
	}for(int i=1;i<=n*2;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=m;i++){
		int u=Q[i].first,v=Q[i].second;
		if(bel[u]!=bel[v]){
			if(lin[u]==v)putchar('1');
			else putchar('2');
		}else putchar('0');
	}puts("");
	return 0;
}
