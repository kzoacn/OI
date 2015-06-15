#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=50010;
typedef long long LL;
int n,K;
struct valvec{
	int a[30];
	void cl(){memset(a,0,sizeof a);}
	int& operator[](int x){return a[x];}
	int operator[](int x)const{return a[x];}
};
valvec operator+(const valvec &ls,const valvec &rs){
	valvec v;
	for(int i=0;i<K;i++)v[i]=ls[i]+rs[i];
	return v;
}
template<typename T>
T in(){
	T r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
vector<int>G[maxn];
int fa[maxn],dep[maxn];
void dfs(int u){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		dep[v]=dep[u]+1;fa[v]=u;
		dfs(v);
	}
}
namespace BF{
	LL p[31];
	valvec a[maxn];
	bool check(valvec &v){
		for(int i=0;i<K;i++)if(v[i]%3)return false;
		return true;
	}
	bool check(int u,int v){
		valvec tmp;tmp.cl();
		if(dep[u]<dep[v])swap(u,v);
		while(dep[u]>dep[v])
			tmp=tmp+a[u],u=fa[u];
		while(u!=v)
			tmp=tmp+a[u],tmp=tmp+a[v],u=fa[u],v=fa[v];
		tmp=tmp+a[u];
		return check(tmp);
	}
	void solve(){
		K=in<int>();
		for(int i=0;i<K;i++)p[i]=in<LL>();
		for(int i=1;i<=n;i++){
			LL x=in<LL>();
			for(int j=0;j<K;j++)while(x%p[j]==0)
				x/=p[j],a[i][j]++;
		}for(int i=1;i<n;i++){
			int u=in<int>(),v=in<int>();
			G[u].push_back(v);
			G[v].push_back(u);			
		}
		LL ans=0;dfs(1);
		for(int i=1;i<=	n;i++)
		for(int j=i;j<=n;j++)
			ans+=check(i,j);
		cout<<ans<<endl;
	}
}
void solve(){

}
int main(){
	freopen("poi.in","r",stdin);
	freopen("poi.out","w",stdout);
	n=in<int>();
	if(n<=100)
		BF::solve();
	else solve();	
	return 0;
}

