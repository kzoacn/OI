#include<bits/stdc++.h>
using namespace std;
const int mo=201314;
const int maxn=50000+5;
int n,q;
int lef[maxn],rig[maxn];
int tot,fa[maxn];
int d[maxn*2];
#define lw(x) (x&-x)
void update(int x,int de){
	while(x<=n*2)
		d[x]+=de,x+=lw(x);
}
int get(int x){
	int ans=0;
	while(x)
		ans+=d[x],x-=lw(x);
	return ans;
}
vector<int>G[maxn];
void dfs(int u){
	lef[u]=++tot;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs(v);
	}rig[u]=++tot;
}
vector<int>b[maxn];
struct qes{
	int l,r,z;
}Q[maxn];

int main(){
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);fa[i]++;
		G[fa[i]].push_back(i);
	}
	
	dfs(1);
	
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].z);
		Q[i].l++;Q[i].r++;Q[i].z++;
		b[Q[i].r].push_back(i);
		b[Q[i].l-1].push_back(i);
	}
	static int anss[maxn];
	for(int i=1;i<=n;i++){
		update(lef[i],1);
		update(rig[i],-1);
		for(int j=0;j<b[i].size();j++){
			int id=b[i][j];
			if(i==Q[id].r){
				anss[id]+=get(lef[Q[id].z]);
			}else{
				anss[id]-=get(lef[Q[id].z]);
			}
		}
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",anss[i]%mo);
	return 0;
}
