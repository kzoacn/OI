#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=305;
struct edge{
	int u,v,w;
	edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
};
int d[maxn],n;
vector<edge>E;
vector<int>G[maxn];
void add(int u,int v,int w){
//	cerr<<u<<" "<<v<<" "<<w<<endl;
	E.push_back(edge(u,v,w));
	G[u].push_back(E.size()-1);
}
void spfa(){
	memset(d,0x7f,sizeof d);
	queue<int>q;q.push(0);d[0]=0;
	static int vis[maxn];
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=E[G[u][i]];
			if(d[u]+e.w<d[e.v]){
				d[e.v]=d[u]+e.w;
				if(!vis[e.v])q.push(e.v),vis[e.v]=1;
			}
		}
	}
}
int a[maxn];
bool exist[maxn];
void great(int x,int y){add(x,y,-1);}
int anss[maxn];
bool check(){
	static int f[maxn];
	f[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=0;
		for(int j=1;j<i;j++)if(anss[j]>anss[i])
			f[i]=max(f[i],f[j]+1);
	}return *max_element(f+1,f+1+n)<3;
}
void sol(){
	scanf("%d",&n);
	E.clear();for(int i=1;i<=n;i++)G[i].clear(),exist[i]=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		if(a[i]==n)continue;
		
		for(int j=1;j<=n;j++)if(exist[j]){
			if(j<a[i])
				great(a[i],j);
			else great(j,a[i]);
		}
		exist[a[i]]=1;
	}
	for(int i=1;i<=n;i++)add(0,i,0);
	add(0,a[n],-1e9);
	spfa();
	static pair<int,int> tmp[maxn];
	for(int i=1;i<=n;i++)tmp[i]=make_pair(d[i],i);
	stable_sort(tmp+1,tmp+1+n);
	int cur=1;
	for(int i=1;i<=n;i++)anss[tmp[i].second]=cur++;
	
	if(anss[n]>anss[n-1]){
		swap(anss[n],anss[n-1]);
		if(!check())
			swap(anss[n],anss[n-1]);
	}
	
	for(int i=1;i<=n;i++)
		printf("%d%c",anss[i]," \n"[i==n]);
}
int main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
