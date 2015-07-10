#include<vector>
#include<cstdio>
#include<queue>
#include<iostream>
#include<algorithm>
#include<map>
//#include<ctime>
using namespace std;
const int maxn=40010;
vector<int>G[maxn];
int fa[maxn],f[maxn],root,siz[maxn],cant[maxn],val[maxn];
int n,All,ans;
void makert(int u){
	siz[u]=1;f[u]=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(cant[v]||fa[u]==v)continue;
		fa[v]=u;
		makert(v);
		siz[u]+=siz[v];
		f[u]=max(f[u],siz[v]);
	}f[u]=max(f[u],All-f[u]);
	if(f[root]>f[u])root=u;
}
struct info{
	int pro,ned,ans,lmx,rmx;
	info(){
		pro=-1;
		ned=0;ans=0;lmx=0;rmx=0;
	}
	info(int val){
		if(val==1){
			pro=1;ned=0;ans=0;lmx=rmx=0;
		}else{
			pro=0;ned=1;ans=0;lmx=rmx=0;
		}
	}
};
info operator+(const info &A,const info &B){
	if(A.pro==-1)return B;
	if(B.pro==-1)return A;
	info I;
	I.ans=max(A.ans,B.ans);
	if(A.pro==B.ned){
		I.ned=A.ned;I.pro=B.pro;
		I.ans=max(A.pro+max(A.rmx,B.lmx),I.ans);
		if(!A.ned)
			I.lmx=max(A.lmx,A.pro+max(A.rmx,B.lmx));
		else I.lmx=A.lmx;
		if(!B.pro)
			I.rmx=max(B.rmx,A.pro+max(A.rmx,B.lmx));
		else I.rmx=B.rmx;
	}else if(A.pro<B.ned){
		I.pro=B.pro;I.ned=B.ned-A.pro+A.ned;
		I.ans=max(A.pro+max(A.rmx,B.lmx),I.ans);
		if(!A.ned)
			I.lmx=max(A.lmx,A.pro+max(A.rmx,B.lmx));
		else I.lmx=A.lmx;	
		if(!B.pro)
			I.rmx=max(B.rmx,A.pro+max(A.rmx,B.lmx));
		else I.rmx=B.rmx;			
	}else{
		I.pro=A.pro-B.ned+B.pro,I.ned=A.ned;
		I.ans=max(B.ned+max(A.rmx,B.lmx),I.ans);
		if(!A.ned)
			I.lmx=max(A.lmx,B.ned+max(A.rmx,B.lmx));
		else I.lmx=A.lmx;
		if(!B.pro)
			I.rmx=max(B.rmx,B.ned+max(A.rmx,B.lmx));
		else I.rmx=B.rmx;				
	}
	return I;
}
bool operator<(const info &A,const info &B){
	return A.rmx<B.rmx;
}
int tot;
info data[maxn];
void dfs(int u,info I){
	I=I+val[u];
	data[++tot]=I;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(cant[v]||fa[u]==v)continue;
		fa[v]=u;
		dfs(v,I);
	}
}
map<int,info>M;
void calc(int u){
	M.clear();
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(cant[v])continue;
		tot=0;fa[v]=0;
		dfs(v,info());
		for(int i=1;i<=tot;i++){
			info I1=data[i];
			ans=max(ans,(val[u]+I1).ans);
			if(!M.count(I1.ned-val[u]))continue;
			info I2=M[I1.ned-val[u]];
			ans=max(ans,((I2+val[u])+I1).ans);
		}
		for(int i=1;i<=tot;i++){
			info I1=data[i];
			if(!M.count(I1.pro))
				M[I1.pro]=I1;
			else if(M[I1.pro]<I1)M[I1.pro]=I1;
		}
	}
}
void solve(int u){
	cant[u]=1;calc(u);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(cant[v])continue;
		f[root=0]=n+1;All=siz[v];
		makert(v);
		solve(root);
	}
}
namespace BF{
	vector<int>G[maxn];
	int fa[maxn];
	int ans=0;
	int sta[maxn],mx[maxn],top,val[maxn],R;
	int cl=0;
	void dfs(int u,int cur,int mx,int dep){
		cl++;
		if(cl>1.5e7){
			cout<<ans<<endl;
			exit(0);
		}
		cur+=val[u];
		if(cur<0)return;
		mx=max(mx,cur);
		if(ans>mx+(R-dep-cur+1)/2)return;
		if(!cur){
	//		if(mx>ans)cerr<<mx<<endl;
			ans=max(ans,mx);
		}
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==fa[u])continue;
			fa[v]=u;
			dfs(v,cur,mx,dep+1);
		}
	}
	int findR(){
		int T=0;T++;
		static int vis[maxn],d[maxn];
		queue<int>q;q.push(1);d[1]=0;vis[1]=1;
		int A=0;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=0;i<G[u].size();i++){
				int v=G[u][i];
				if(vis[v]==T)continue;
				vis[v]=T;d[v]=d[u]+1;q.push(v);
				if(d[v]>d[A])A=v;
			}
		}
		q.push(A);d[A]=0;vis[A]=++T;
		int ans=0;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=0;i<G[u].size();i++){
				int v=G[u][i];
				if(vis[v]==T)continue;
				vis[v]=T;d[v]=d[u]+1;q.push(v);
				if(d[v]>ans)ans=d[v];
			}
		}
		return ans;
	}
	int solve(){
		
		for(int i=2;i<=n;i++){
			scanf("%d",&fa[i]);
			G[fa[i]].push_back(i);
			G[i].push_back(fa[i]);
		}mx[0]=-1e9;
		
		for(int i=1;i<=n;i++){
			char s[2];scanf("%s",s);
			val[i]=*s=='('?1:-1;
		}
		
		R=findR();
		
		for(int i=1;i<=n;i++)
			fa[i]=0,dfs(i,0,0,0);
		
		cout<<ans<<endl;
		return 0;
	}
}
int main(){
	freopen("deep.in","r",stdin);
	freopen("deep.out","w",stdout);
	scanf("%d",&n);
	
	if(n<=2500)return BF::solve();
	
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);
		G[fa[i]].push_back(i);
		G[i].push_back(fa[i]);
	}
	
	for(int i=1;i<=n;i++){
		char s[2];scanf("%s",s);
		val[i]=*s=='('?1:-1;
	}


	
	f[root=0]=n+1;All=n;
	makert(1);
	solve(root);
	
	cout<<ans<<endl;
	return 0;
}
