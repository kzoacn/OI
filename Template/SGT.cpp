#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct sgt{
	#define lson i<<1,l,(l+r)/2
	#define rson i<<1|1,(l+r)/2+1,r
	#define ls i<<1
	#define rs i<<1|1
	struct node{
		int lazy,sum;
	}t[maxn<<2];
	void rz(int i){
		t[i].sum=t[ls].sum+t[rs].sum;
	}
	void pd(int i,int l,int r){
		if(t[i].lazy!=-1){
			t[ls].sum=0;
			t[rs].sum=0;
			t[ls].lazy=0;
			t[rs].lazy=0;
			t[i].lazy=-1;
		}
	}
	void build(int i,int l,int r){
		if(l==r){t[i].sum=1;t[i].lazy=-1;return;}
		build(lson);build(rson);rz(i);
	}
	void set0(int i,int l,int r,int l0,int r0){
		if(l0<=l&&r0>=r){t[i].sum=t[i].lazy=0;return;}pd(i,l,r);
		if(l0<=(l+r)/2)set0(lson,l0,r0);
		if(r0>(l+r)/2)set0(rson,l0,r0);
		rz(i);
	}
	int get(int i,int l,int r,int ps){
		if(l==r)return t[i].sum;pd(i,l,r);
		if(ps<=(l+r)/2)return get(lson,ps);
		else return get(rson,ps);	
	}
}T;
int main(){
	
	return 0;
}
