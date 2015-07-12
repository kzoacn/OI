#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;
const int maxn=1e5+5;
struct P{
	int x,y;
	P(int x=INT_MIN,int y=INT_MIN):x(x),y(y){}
};
int tot=0;
int X[maxn],Y[maxn];
int X1,X2,Y1,Y2;
P operator+(const P &a,const P &b){
	return P(a.x+b.x,a.y+b.y);
}
bool operator<(const P &a,const P &b){
	return a.x<b.x&&a.y<b.y;
}
bool operator<=(const P &a,const P &b){
	return a.x<=b.x&&a.y<=b.y;
}
struct node{
	P mnx,mny,mxx,mxy,all;
	int sum;
	int l,r;
	void rz();
	node(){sum=0;l=r=0;mnx=mny=mxx=mxy=P();all=P(0,0);}
	void pd();
}t[maxn*2];
bool byX(P a,P b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
bool byY(P a,P b){return a.y!=b.y?a.y<b.y:a.x<b.x;}
void node::rz(){
	sum=t[l].sum+t[r].sum;
	vector<P>vec;
	vec.push_back(t[l].mnx);
	vec.push_back(t[l].mxx);
	vec.push_back(t[l].mny);
	vec.push_back(t[l].mxy);
	vec.push_back(t[r].mnx);
	vec.push_back(t[r].mxx);
	vec.push_back(t[r].mny);
	vec.push_back(t[r].mxy);
	sort(vec.begin(),vec.end(),byX);
	mnx=P(-2e9,-2e9);
	mny=P(-2e9,-2e9);
	mxx=P(-2e9,-2e9);
	mxy=P(-2e9,-2e9);
	for(int i=0;i<vec.size();i++){
		if(Y1<=vec[i].y&&vec[i].y<=Y2){
			if(vec[i].x<X1)
			mnx=max(mnx,vec[i],byX);
		}	
	}
	for(int i=0;i<vec.size();i++){
		if(Y1<=vec[i].y&&vec[i].y<=Y2){
			if(vec[i].x<=X2)
			mxx=max(mxx,vec[i],byX);
		}	
	}
	sort(vec.begin(),vec.end(),byY);
	for(int i=0;i<vec.size();i++){
		if(X1<=vec[i].x&&vec[i].x<=X2){
			if(vec[i].y<Y1)
			mny=max(mny,vec[i],byY);
		}	
	}
	for(int i=0;i<vec.size();i++){
		if(X1<=vec[i].x&&vec[i].x<=X2){
			if(vec[i].y<=Y2)
			mxy=max(mxy,vec[i],byY);
		}	
	}
}
void node::pd(){
	t[l].mnx=t[l].mnx+all;
	t[l].mny=t[l].mny+all;
	t[l].mxx=t[l].mxx+all;
	t[l].mxy=t[l].mxy+all;
	t[r].mnx=t[r].mnx+all;
	t[r].mny=t[r].mny+all;
	t[r].mxx=t[r].mxx+all;
	t[r].mxy=t[r].mxy+all;
	all=P(0,0);
}
int in(const P &p){
	return X1<=p.x&&p.x<=X2&&Y1<=p.y&&p.y<=Y2;
}
int build(int l,int r){
	int x=++tot;
	if(l==r){
		t[x].mnx=t[x].mxx=t[x].mny=t[x].mxy=P(X[l],Y[l]);
		t[x].sum=in(P(X[l],Y[l]));
		return x;
	}
	int mid=(l+r)/2;
	t[x].l=build(l,mid);
	t[x].r=build(mid+1,r);
	t[x].rz();
	return x;
}
int n;
#define lson t[x].l,l,mid
#define rson t[x].r,mid+1,r
void Add(int x,int l,int r,int l0,int r0,P d){
	if(l==r){
		t[x].mnx=t[x].mnx+d;
		t[x].mny=t[x].mny+d;
		t[x].mxx=t[x].mxx+d;
		t[x].mxy=t[x].mxy+d;
		t[x].sum=in(t[x].mnx);
		return;
	}
	if(l0<=l&&r0>=r){
		if(!(in(t[x].mnx)^in(t[x].mnx+d))
			&&!(in(t[x].mny)^in(t[x].mny+d))
			&&!(in(t[x].mxx)^in(t[x].mxx+d))
			&&!(in(t[x].mxy)^in(t[x].mxy+d))){
		t[x].mnx=t[x].mnx+d;
		t[x].mny=t[x].mny+d;
		t[x].mxx=t[x].mxx+d;
		t[x].mxy=t[x].mxy+d;
				
			t[x].all=t[x].all+d;
			return;
		}
	}t[x].pd();
	int mid=(l+r)>>1;
	if(l0<=mid)Add(lson,l0,r0,d);
	if(r0>mid)Add(rson,l0,r0,d);
	t[x].rz();
}
int Qsum(int x,int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)return t[x].sum;
	int mid=(l+r)>>1,ans=0;
	t[x].pd();
	if(l0<=mid)ans+=Qsum(lson,l0,r0);
	if(r0>mid)ans+=Qsum(rson,l0,r0);
	return ans;
}
void sol(){
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++)t[i]=node();
	scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
	for(int i=1;i<=n;i++)scanf("%d%d",&X[i],&Y[i]);
	tot=0;
	build(1,n);
	int m;scanf("%d",&m);
	while(m--){
		int ty;scanf("%d",&ty);
		int l,r,d;scanf("%d%d",&l,&r);
		if(ty==1){
			scanf("%d",&d);
			Add(1,1,n,l,r,P(d,0));	
		}else if(ty==2){
			scanf("%d",&d);
			Add(1,1,n,l,r,P(0,d));	
		}else{
			printf("%d\n",Qsum(1,1,n,l,r));
		}
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
