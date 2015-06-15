#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m,p,X;
int a[maxn],cir[maxn],dep[maxn],vis[maxn];
void dfs(int x){
	if(vis[x]==X){
		if(x==X)cir[x]=1;
		return;
	}vis[x]=X;dfs(x*x%p);
}
void dfs(int x,int d){
	if(cir[x])return void(dep[x]=d);
	dfs(x*x%p,d+1);
}
struct info{
	int cur;
	vector<int>vec;
	bool ci;
	info(){cur=0;ci=0;}
	int sum(){return vec[cur];}
};
struct flag{
	int add;
	flag(int add=0):add(add){};
};
int lcm(int x,int y){return x*y/__gcd(x,y);}
info operator+(const info &ls,const info &rs){
	info in;
	in.ci=ls.ci&rs.ci;
	if(in.ci){
		in.vec.clear();
		int cu1=ls.cur,cu2=rs.cur;
		int l=lcm(ls.vec.size(),rs.vec.size());
		for(int i=0;i<l;i++){
			in.vec.push_back(ls.vec[cu1]+rs.vec[cu2]);
			cu1=(cu1+1)%ls.vec.size();
			cu2=(cu2+1)%rs.vec.size();
		}
	}else{
		in.vec.clear();
		in.vec.push_back(ls.vec[0]+rs.vec[0]);
	}return in;
}
info operator+(const flag &ls,const info &rs){
	info in=rs;
	if(in.ci)
		in.cur=(in.cur+ls.add)%in.vec.size();
	else{
		int t=ls.add;
		
	}return in;
}
flag operator+(const flag &ls,const flag &rs){
	return flag(ls.add+rs.add);
}
#define lson i<<1,l,(l+r)/2
#define rson i<<1|1,(l+r)/2+1,r
#define ls i<<1
#define rs i<<1|1
vector<int>get(int x){
	vector<int>vec;
	vec.push_back(x);
	do{
		x=x*x%p;
		vec.push_back(x);
	}while(x!=vec.front());
	vec.pop_back();
	return vec;
}
struct sgt{
	info Info[maxn<<2];
	flag Flag[maxn<<2];
	void pd(int i){
		if(!Flag[i].add)return;
		Info[ls]=Flag[i]+Info[ls];
		Info[rs]=Flag[i]+Info[rs];
		Flag[ls]=Flag[i]+Flag[ls];
		Flag[rs]=Flag[i]+Flag[rs];
		Flag[i].add=0;		
	}
	void build(int i,int l,int r){
		if(l==r){
			if(cir[a[l]]){
				Info[i].vec=get(a[l]);
				Info[i].ci=1;
			}else{
				Info[i].vec.push_back(a[l]);
				Info[i].ci=0;
			}
			return;
		}build(lson);build(rson);
		Info[i]=Info[ls]+Info[rs];
	}
	int Q(int i,int l,int r,int l0,int r0){
		if(l0<=l&&r0>=r)return Info[i].sum();
		int ans=0;
		if(l0<=(l+r)/2)ans+=Q(lson,l0,r0);
		if(r0>(l+r)/2)ans+=Q(rson,l0,r0);
		return ans;
	}
	void C(int i,int l,int r,int l0,int r0){
		if(l==r){
			Info[i].vec[0]=Info[i].vec[0]*Info[i].vec[0]%p;
			Info[i].ci=cir[Info[i].vec[0]];
			if(Info[i].ci)
				Info[i].vec=get(Info[i].vec[0]);
			return;
		}
		if(l0<=l&&r0>=r&&Info[i].ci){
			Info[i]=flag(1)+Info[i];
			return;
		}pd(i);
		if(l0<=(l+r)/2)C(lson,l0,r0);
		if(r0>(l+r)/2)C(rson,l0,r0);
		Info[i]=Info[ls]+Info[rs];
	}
}T;
void C(int l,int r){
	for(int i=l;i<=r;i++)
		a[i]=a[i]*a[i]%p;
}
int Q(int l,int r){return accumulate(a+l,a+r+1,0);}
int main(){
	freopen("bzoj4105.in","r",stdin);
	n=in();m=in();p=in();
	for(int i=1;i<=n;i++)a[i]=in();
	for(int i=0;i<p;i++)X=i,dfs(i);
	for(int i=0;i<p;i++)dfs(i,0);
	T.build(1,1,n);
	while(m--){
		int op=in();
		int l=in(),r=in();
		if(op==0)C(l,r);
		else printf("%d\n",Q(l,r));
	}
	return 0;
}
