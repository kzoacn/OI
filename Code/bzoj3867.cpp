#include<bits/stdc++.h>
using namespace std;
int a[100001];
struct node{
	int all,mx,sa;
	int l,r;
	node(){all=-1;mx=-1;sa=-1;l=r=0;}
	void rz();
}t[200001];
#define ls t[i].l
#define rs t[i].r
int tot;
void pd(int i){
	if(t[i].all>=0){
		t[ls].all=t[ls].mx=t[ls].sa=t[i].all;
		t[rs].all=t[rs].mx=t[rs].sa=t[i].all;
		t[i].all=-1;
	}
}
void node::rz(){
	mx=max(t[l].mx,t[r].mx);
	sa=t[l].sa==t[r].sa?t[r].sa:-1;
}
int build(int l,int r){
	int x=++tot;
	if(l==r){t[x].mx=a[l];t[x].sa=a[l];return x;}
	t[x].l=build(l,(l+r)/2);
	t[x].r=build((l+r)/2+1,r);
	t[x].rz();return x;
}
void C(int i,int l,int r,int l0,int r0,int x){
	if(l0<=l&&r0>=r){
		t[i].all=x;t[i].sa=x;t[i].mx=x;
		return;
	}pd(i);
	if(l0<=(l+r)/2)C(ls,l,(l+r)/2,l0,r0,x);
	if(r0>(l+r)/2)C(rs,(l+r)/2+1,r,l0,r0,x);
	t[i].rz();
}
void G(int i,int l,int r,int l0,int r0,int x){
	if(t[i].mx<=x)return;
	if(l==r){
		t[i].mx=t[i].all=t[i].sa=__gcd(x,t[i].mx);
		return;	
	}
	if(l0<=l&&r0>=r&&t[i].sa!=-1){
		t[i].mx=t[i].all=t[i].sa=__gcd(x,t[i].mx);
		return;
	}pd(i);
	if(l0<=(l+r)/2)G(ls,l,(l+r)/2,l0,r0,x);
	if(r0>(l+r)/2)G(rs,(l+r)/2+1,r,l0,r0,x);
	t[i].rz();
}
void dfs(int i,int l,int r){
	if(l==r){a[l]=t[i].sa;return;}
	pd(i);
	dfs(ls,l,(l+r)/2);
	dfs(rs,(l+r)/2+1,r);
}
void sol(){
	int n,m;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=tot;i++)t[i]=node();tot=0;
	build(1,n);
	scanf("%d",&m);
	while(m--){
		int ty;scanf("%d",&ty);
		int l,r,x;scanf("%d%d%d",&l,&r,&x);
		if(ty==1){
			C(1,1,n,l,r,x);
		}else{
			G(1,1,n,l,r,x);
		}
	}dfs(1,1,n);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
}
int main(){
	freopen("bzoj3867.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
