#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m,q;
struct edge{
	int u,v,w;
	bool operator<(const edge &o)const{
		return w<o.w;
	}
}E[maxn];
int vis[maxn];
struct ufset{
	int fa[maxn],used[maxn*2],z,T,vis[maxn];
	ufset(){T=1;}
	void init(){for(int i=1;i<=n;i++)fa[i]=i;}
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
	void merge(int x,int y){
		if(vis[x]!=T)used[++z]=x;
		if(vis[y]!=T)used[++z]=y;
		vis[x]=vis[y]=T;
		fa[find(x)]=find(y);
	}
	void reset(){
		T++;
		for(int i=1;i<=z;i++)fa[used[i]]=used[i];
		z=0;
	}
	bool con(int x,int y){return find(x)==find(y);}
}F;
struct qes{int u,v;}Q[maxn];
int anss[maxn];
void sol1(){
	sort(E,E+m);
	F.init();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)scanf("%d%d",&Q[i].u,&Q[i].v);
	for(int i=0;i<=m;i++){
		if(i==m||(i&&E[i].w!=E[i-1].w)){
			for(int j=1;j<=q;j++){
				int u=Q[j].u,v=Q[j].v;
				if(F.con(u,v))anss[j]++;
			}F.reset();
		}F.merge(E[i].u,E[i].v);
	}for(int i=1;i<=q;i++)printf("%d\n",anss[i]/2);
}
vector<int>Qu[maxn];
void sol2(){
	sort(E,E+m);
	F.init();
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&Q[i].u,&Q[i].v);
		Qu[Q[i].u].push_back(i);
		Qu[Q[i].v].push_back(i);
	}
	for(int i=0;i<=m;i++){
		if(i==m||(i&&E[i].w!=E[i-1].w)){
			for(int j=1;j<=F.z;j++){
				int x=F.used[j];
				for(int k=0;k<Qu[x].size();k++){
					int u=Q[Qu[x][k]].u,v=Q[Qu[x][k]].v;
					if(F.con(u,v))anss[Qu[x][k]]++;
				}
			}
			F.reset();
		}F.merge(E[i].u,E[i].v);
	}for(int i=1;i<=q;i++)printf("%d\n",anss[i]/2);	
}
int main(){
	scanf("%d%d",&n,&m);int sqrtm=0;
	for(int i=0;i<m;i++)scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w),sqrtm+=!vis[E[i].w],vis[E[i].w]=1;
//	if(sqrtm<=sqrt(m))
		sol1();
//	else 
//		sol2();
	return 0;
}
