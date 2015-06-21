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
void dfs(int u){
	lef[u]=++tot;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs(v);
	}rig[u]=tot;
}
int build(int l,int r){
	int x=++tot;
	t[x]=node();
	if(l==r){
		t[x].c=1;
		return x;
	}
	t[x].l=build(l,(l+r)/2);
	t[x].r=build(1+(l+r)/2,r);
	return x;
}
int Q(int i,int l,int r,int ps){
	if(l==r)return t[i].c;
	t[i].pd();
	if(ps<=(l+r)/2)return Q(t[i].l,l,(l+r)/2,ps);
	else return Q(t[i].r,(l+r)/2+1,r,ps);
}
void C(int i,int l,int r,int l0,int r0,int c){
	if(l0<=l&&r0>=r){
		t[i].al=t[i].c=c;
		return;
	}t[i].pd();
	int mid=(l+r)/2;
	if(l0<=mid)C(t[i].l,l,mid,l0,r0,c);
	if(r0>mid)C(t[i].r,mid+1,r,l0,r0,c);
	return;
}
void sol(){
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=2;i<=n;i++){
		int u;scanf("%d",&u);
		fa[i]=u;G[u].push_back(i);
	}
	tot=0;
	dfs(1);
	tot=0;
	build(1,n);
	long long sum=0;
	for(int i=1;i<=m;i++){
		int a,l,c;scanf("%d%d%d",&a,&l,&c);
		if(!c){
			int an=Q(1,1,n,lef[a]);
		//	cerr<<an<<endl;
			sum=(sum+(long long)i*an)%int(1e9+7);
		}else{
			if(l==0){
				C(1,1,n,lef[a],lef[a],c);
			}else
			if(l==1){
				C(1,1,n,lef[a],lef[a],c);
				for(int i=0;i<G[a].size();i++){
					int v=G[a][i];
					C(1,1,n,lef[v],lef[v],c);
				}
			}else{
				C(1,1,n,lef[a],rig[a],c);
			}
		}
	}cout<<sum%int(1e9+7)<<endl;
}
int main(){
//	freopen("g1.in","r",stdin);
//	freopen("g1.out","w",stdout);
	int T;cin>>T;
	while(T--)sol();	
	return 0;
}
