#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,s,m;
int ss[maxn];
struct edge{
	int u,v,w;
	bool operator<(const edge &o)const{return w<o.w;}
}E[maxn];
vector<edge>G[maxn];
struct qes{
	int u,v,w,id;
	bool operator<(const qes o)const{return w<o.w;}
}Q[maxn];
int anss[maxn],Es;
void spfa(){
	static int d[maxn],vis[maxn];
	memset(d,0x7f,sizeof d);
	queue<int>q;
	for(int i=1;i<=s;i++){
		vis[ss[i]]=1;
		q.push(ss[i]);
		d[ss[i]]=0;
	}
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=G[u][i];
			if(d[e.v]>d[u]+e.w){
				d[e.v]=d[u]+e.w;
				if(!vis[e.v])vis[e.v]=1,q.push(e.v);
			}
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=0;j<G[i].size();j++){
		edge e=G[i][j];
		if(e.u>e.v)continue;
		E[Es++]=(edge){e.u,e.v,d[e.u]+d[e.v]+e.w};
	}
}
int fa[maxn];
void init(){for(int i=1;i<=n;i++)fa[i]=i;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
int main(){
	freopen("bzoj4144.in","r",stdin);
	scanf("%d%d%d",&n,&s,&m);
	for(int i=1;i<=s;i++)scanf("%d",&ss[i]);
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
	}int q;scanf("%d",&q);
	for(int i=1;i<=q;i++)scanf("%d%d%d",&Q[i].u,&Q[i].v,&Q[i].w),Q[i].id=i;
	sort(Q+1,Q+1+q);
	spfa();
	E[Es++]=(edge){0,0,int(2e9)};
	sort(E,E+Es);
	init();
	int cur=1;
	for(int i=0;i<Es;i++){
		edge e=E[i];
		while(cur<=q&&e.w>Q[cur].w){
			anss[Q[cur].id]=find(Q[cur].u)==find(Q[cur].v);
			cur++;
		}
		merge(e.u,e.v);
	}	
	for(int i=1;i<=q;i++)printf("%s\n",anss[i]?"TAK":"NIE");
	return 0;
}
