#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+6;
int tot=0;
struct sgtnode{
	int id;
	int l,r;	
}tr[3967332];
struct sgt{
	int rt,n;
	int build(int l,int r){
		int x=++tot;
		tr[x].id=0;tr[x].l=tr[x].r=0;
		if(l==r)return x;
		int mid=(l+r)/2;
		tr[x].l=build(l,mid);
		tr[x].r=build(mid+1,r);
		return x;
	}
	void build(int _n){
		n=_n;
		rt=build(1,n);
	}
	int Qmax(int x,int l,int r,int ps){
		if(l==r)return tr[x].id;
		int mid=(l+r)/2;
		if(ps<=mid)return max(Qmax(tr[x].l,l,mid,ps),tr[x].id);
		else return max(Qmax(tr[x].r,mid+1,r,ps),tr[x].id);
	}
	void C(int x,int l,int r,int l0,int r0,int id){		
		if(l0<=l&&r0>=r)return void(tr[x].id=id);
		int mid=(l+r)/2;
		if(l0<=mid)C(tr[x].l,l,mid,l0,r0,id);
		if(r0>mid)C(tr[x].r,mid+1,r,l0,r0,id);
	}
	int Qmax(int ps){return Qmax(rt,1,n,ps);}
	void C(int l0,int r0,int id){C(rt,1,n,l0,r0,id);}
};
int n,m,c;
vector<int>G[maxn];
int dep[maxn],timc[maxn]={1},fa[maxn],lef[maxn],rig[maxn],tmz;
vector<int>deps[maxn];
vector<int>tmp;
void dfs(int u){
	lef[u]=++tmz;
	deps[dep[u]].push_back(lef[u]);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dep[v]=dep[u]+1;
		dfs(v);
	}rig[u]=tmz;
}
int z;
struct node{
	sgt T;
	vector<int>v;
	int l,r;
}t[maxn*2];
int build(int l,int r){
	int x=++z;
	for(int i=l;i<=r;i++)
		tmp.insert(tmp.end(),deps[i].begin(),deps[i].end());
	t[x].T.build(tmp.size());
	sort(tmp.begin(),tmp.end());
	t[x].v=tmp;
	tmp.clear();
	if(l==r)return x;
	int mid=(l+r)/2;
	t[x].l=build(l,mid);
	t[x].r=build(mid+1,r);
	return x;
}
void C(int x,int l,int r,int a,int l0,int r0,int id){
	if(l0<=l&&r0>=r){
		int L=lower_bound(t[x].v.begin(),t[x].v.end(),lef[a])-t[x].v.begin()+1;
		int R=upper_bound(t[x].v.begin(),t[x].v.end(),rig[a])-t[x].v.begin();
		if(L<=R)
		t[x].T.C(L,R,id);
		return;
	}
	int mid=(l+r)/2;
	if(l0<=mid)C(t[x].l,l,mid,a,l0,r0,id);
	if(r0>mid)C(t[x].r,mid+1,r,a,l0,r0,id);
}
int Qmax(int x,int l,int r,int a){	
	int ps=lower_bound(t[x].v.begin(),t[x].v.end(),lef[a])-t[x].v.begin()+1;
	int ans=0;
	ans=t[x].T.Qmax(ps);
	if(l==r)return ans;
	int mid=(l+r)>>1;
	if(dep[a]<=mid)ans=max(ans,Qmax(t[x].l,l,mid,a));
	else ans=max(ans,Qmax(t[x].r,mid+1,r,a));
	return ans;
}
void sol(){
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);
		G[fa[i]].push_back(i);
	}dep[1]=1;tot=0;z=0;tmz=0;
	dfs(1);
	int H=*max_element(dep+1,dep+1+n);
	build(1,H);
	//cerr<<tot<<endl;
	for(int i=1;i<=H;i++)deps[i].clear();
	long long sum=0;
	for(int i=1;i<=m;i++){
		int a,l,c;scanf("%d%d%d",&a,&l,&c);
		if(!c){
			int ans=timc[Qmax(1,1,H,a)];
			//cerr<<ans<<endl;
			sum+=(long long)i*ans;
			sum%=int(1e9+7);
		}else{
			timc[i]=c;
			int l0=dep[a],r0=min(H,dep[a]+l);
			C(1,1,H,a,l0,r0,i);
		}
	}cout<<sum<<endl;
}
int main(){
//	freopen("g.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
