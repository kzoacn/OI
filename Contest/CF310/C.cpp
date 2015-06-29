#include<bits/stdc++.h>
using namespace std;
struct node{
	int laz;
	node *l,*r;
	node(){l=r=0;laz=0;}
	void pd(){
		if(laz==0)return;
		if(!l)l=new node();
		if(!r)r=new node();
		l->laz=max(l->laz,laz);
		r->laz=max(r->laz,laz);
	}
}*T1=new node(),*T2=new node();
void C(node *&x,int l,int r,int l0,int r0,int d){
	if(!x)x=new node();
	if(l0<=l&&r0>=r){
		x->laz=max(x->laz,d);
		return;
	}x->pd();
	int mid=(l+r)/2;
	if(l0<=mid)C(x->l,l,mid,l0,r0,d);
	if(r0>mid)C(x->r,mid+1,r,l0,r0,d);
}
int Q(node *&x,int l,int r,int ps){
	if(!x)return 0;
	if(l==r)return x->laz;
	x->pd();int mid=(l+r)/2;
	if(ps<=mid)return Q(x->l,l,mid,ps);
	else return Q(x->r,mid+1,r,ps);
}
int n,q;
map<int,int>M;
int main(){
	scanf("%d%d",&n,&q);
	while(q--){
		int x,y;char ty[2];
		scanf("%d%d%s",&x,&y,ty);
		if(M[x]){puts("0");continue;}
		M[x]=1;
		if(*ty=='U'){
			int z=Q(T1,1,n,x);	
			printf("%d\n",y-z);
			C(T2,1,n,z+1,y,x);
		}else{
			int z=Q(T2,1,n,y);
			printf("%d\n",x-z);
			C(T1,1,n,z+1,x,y);
		}
	}
	return 0;
}
