#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m,c;
struct node{
	int al,c;
	void pd();
	int l,r;
	node(){al=c=l=r=0;}
}t[maxn*2];
int tot=0;
void node::pd(){
	if(al==0)return;
	t[l].c=t[l].al=al;
	t[r].c=t[r].al=al;
	al=0;
}
int lef[maxn],rig[maxn],fa[maxn];
vector<int>G[maxn];
int col[maxn];
int L;
void dfs(int u,int c,int dep){
	if(dep>L)return;
	col[u]=c;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs(v,c,dep+1);
	}
}
void sol(){
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=2;i<=n;i++){
		int u;scanf("%d",&u);
		fa[i]=u;G[u].push_back(i);
	}
	for(int i=1;i<=n;i++)col[i]=1;
	long long sum=0;
	for(int i=1;i<=m;i++){
		int a,l,c;scanf("%d%d%d",&a,&l,&c);
		if(!c){
			int an=col[a];
		//	cerr<<an<<endl;
			sum=(sum+(long long)i*an)%int(1e9+7);
		}else{
			L=l;
			dfs(a,c,0);
		}
	}cout<<sum%int(1e9+7)<<endl;
}
int main(){
	freopen("g1.in","r",stdin);
	freopen("g1.out","w",stdout);
	int T;cin>>T;
	while(T--)sol();	
	return 0;
}
