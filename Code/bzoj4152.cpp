#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n;
struct P{
	int x,y,id;
}p[maxn];
bool byX(const P &a,const P &b){return a.x<b.x;}
bool byY(const P &a,const P &b){return a.y<b.y;}
struct edge{int u,v,w;};
vector<edge>G[maxn];
void add(int u,int v,int w){
	G[u].push_back((edge){u,v,w});
	G[v].push_back((edge){v,u,w});
}
typedef pair<int,int>  p
void spfa(){
	static int d[maxn],vis[maxn];
	memset(d,0x7f,sizeof d);d[1]=0;
	priority_queue<int,ve>q;q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=G[u][i];
			if(d[e.v]>d[u]+e.w){
				d[e.v]=d[u]+e.w;
				if(!vis[e.v])vis[e.v]=1,q.push(e.v);
			}
		}
	}printf("%d\n",d[n]);
}
int main(){
	freopen("bzoj4152.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y),p[i].id=i;
	sort(p+1,p+1+n,byX);
	for(int i=1;i<n;i++)
	add(p[i].id,p[i+1].id,p[i+1].x-p[i].x);
	sort(p+1,p+1+n,byY);	
	for(int i=1;i<n;i++)
	add(p[i].id,p[i+1].id,p[i+1].y-p[i].y);
	spfa();
	return 0;
}
