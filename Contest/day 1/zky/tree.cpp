#include<cstring>
#include<cctype>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int maxn=1e4+4;
typedef unsigned long long UL;
UL h[maxn];
int f[maxn],fa[maxn];
int col[maxn];
vector<int>G[maxn];
int n,pre[maxn],siz[maxn];
int A,B;
int findR(){
	static int TT=0;
	TT++;
	static int vis[maxn],d[maxn];
	queue<int>q;q.push(1);vis[1]=TT;d[1]=0;
	A=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v]==TT)continue;
			vis[v]=TT;d[v]=d[u]+1;
			q.push(v);
			if(d[v]>d[A])A=v;
		}
	}
	B=0;
	TT++;
	vis[A]=TT;d[A]=0;q.push(A);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v]==TT)continue;
			vis[v]=TT;d[v]=d[u]+1;
			q.push(v);pre[v]=u;
			if(d[v]>d[B])B=v;
		}
	}return d[B];
}
int tmp[maxn];
bool cmp(int x,int y){return h[x]<h[y];}
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		fa[v]=u;dfs(v);
		siz[u]+=siz[v];
	}tmp[0]=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		tmp[++tmp[0]]=v;
	}	
	sort(tmp+1,tmp+1+tmp[0],cmp);h[u]=0;UL sum=0;
	for(int i=1;i<=tmp[0];i++)h[u]=h[u]*233+h[tmp[i]],sum^=h[tmp[i]];
	h[u]=h[u]*233+col[u];
	if(sum!=0){
		int v=0;
		for(int i=1;i<=tmp[0];i++)if(sum==h[tmp[i]]){v=tmp[i];break;}
		if(!v)f[u]=0;
		else if(f[v])f[u]=1;
		else f[u]=0;
	}else f[u]=1;
}
int D;
void P(){
	D/=2;
	int O=B;while(D--)O=pre[O];
	dfs(O);tmp[0]=0;
	for(int i=0;i<G[O].size();i++)tmp[++tmp[0]]=G[O][i];
	sort(tmp+1,tmp+1+tmp[0],cmp);
	int dif=0,flag=1;
	for(int i=1;i<=tmp[0];){
		if(i==tmp[0]||h[tmp[i]]!=h[tmp[i+1]]){
			if(f[tmp[i]])dif++;
			else flag=0;
			i+=1;
		}else i+=2;
	}
	if(!flag||dif>2)
		puts("NOT SYMMETRIC");
	else puts("SYMMETRIC");
}
void C(){
	D/=2;
	while(D--)B=pre[B];
	A=pre[B];
	fa[A]=B;fa[B]=A;
	dfs(A);
	dfs(B);
	if(h[A]==h[B]||(f[A]&&f[B]))
		puts("SYMMETRIC");
	else puts("NOT SYMMETRIC");
}
void sol(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)h[i]=f[i]=fa[i]=pre[i]=0;
	for(int i=1;i<=n;i++){
		char c[2];scanf("%s",c);
		col[i]=*c;
	}
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	D=findR();
	if(D%2==0)
		P();
	else C();
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
