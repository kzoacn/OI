#include<bits/stdc++.h>
using namespace std;
const double eps=1e-5;
const int maxn=1e5+5;
int dcmp(double x){return (x>eps)-(x<-eps);}
int n,L,U;
double lim;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
double ans;
struct edge{int u,v,w;};
vector<edge>G[maxn];
int root,All;
short cant[maxn];
int siz[maxn],f[maxn],fa[maxn];
void makert(int u,int &root){
	siz[u]=1;f[u]=0;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];if(cant[e.v]||e.v==fa[u])continue;
		fa[e.v]=u;
		makert(e.v,root);
		siz[u]+=siz[e.v];
		f[u]=max(f[u],siz[e.v]);
	}f[u]=max(f[u],All-f[u]);
	if(f[root]>f[u])root=u;
}
double mx[maxn],d[maxn];
int data[maxn],dep[maxn];
bool ok(int u,double mid){
	int size=0;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];if(cant[e.v])continue;data[0]=0;fa[e.v]=u;
		queue<int>q;q.push(e.v);d[e.v]=e.w-mid;dep[e.v]=1;
		while(!q.empty()){
			int u=q.front();q.pop();data[++data[0]]=u;
			for(int i=0;i<G[u].size();i++){
				edge e=G[u][i];if(cant[e.v]||fa[u]==e.v)continue;
				fa[e.v]=u;dep[e.v]=dep[u]+1;q.push(e.v);
				d[e.v]=d[u]+e.w-mid;
			}
		}deque<int>dq;int now=size;
		for(int j=1;j<=data[0];j++){
			int u=data[j];
			while(now>=0&&dep[u]+now>=L){
				while(dq.size()&&mx[dq.back()]<mx[now])dq.pop_back();
				dq.push_back(now--);
			}while(dq.size()&&dq.front()+dep[u]>U)dq.pop_front();
			if(dq.size()&&d[u]+mx[dq.front()]>=0)return 1;
		}for(int j=size+1;j<=dep[data[data[0]]];j++)mx[j]=-1e10;
		for(int j=1;j<=data[0];j++){
			int u=data[j];
			mx[dep[u]]=max(mx[dep[u]],d[u]);
		}size=max(size,dep[data[data[0]]]);	
	}return 0;
}
void calc(int u){
	double l=ans,r=lim;
	while(dcmp(l-r)){
		double mid=(l+r)*.5;
		if(ok(u,mid))l=mid;
		else r=mid;
	}ans=l;
}
void solve(int u){
	calc(u);cant[u]=1;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];if(cant[e.v]||siz[e.v]<L)continue;
		f[root=0]=n+1;All=siz[e.v];
		makert(e.v,root);
		solve(root);
	}
}
int main(){
	n=getint();L=getint();U=getint();All=n;
	for(int i=1;i<n;i++){
		int u=getint(),v=getint(),w=getint();
		lim=max(lim,double(w));
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
	}f[root=0]=n+1;
	makert(1,root);
	solve(root);
	cout<<fixed<<setprecision(3)<<ans<<endl;
	return 0;
}
