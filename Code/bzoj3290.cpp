#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m;
struct P{
	int x[3];
	int& operator[](const int &a){return a[x];}
	int operator[](const int &a)const{return a[x];}
	bool operator==(const P &p)const{
		return x[0]==p[0]&&x[1]==p[1]&&x[2]==p[2];
	}
	bool operator<(const P &p)const{
		return x[0]!=p[0]?x[0]<p[0]:(x[1]!=p[1]?x[1]<p[1]:x[2]<p[2]);
	}
	P(){}
}p[maxn*2],_p[maxn*2];
struct R{
	int mn[3],mx[3];
	R(P p=P()){for(int i=0;i<3;i++)mx[i]=mn[i]=p[i];}
};
R operator+(const R &ls,const R &rs){
	R r=ls;
	for(int i=0;i<3;i++){
		r.mn[i]=min(r.mn[i],rs.mn[i]);
		r.mx[i]=max(r.mx[i],rs.mx[i]);
	}return r;
}
inline bool In(const P &A,const R &B){
	for(register int i=0;i<3;i++){
		if(A[i]>B.mx[i]||A[i]<B.mn[i])
			return false;
	}return true;
}
inline bool In(const R &A,const R &B){
	for(register int i=0;i<3;i++){
		if(!(B.mn[i]<=A.mn[i]&&A.mx[i]<=B.mx[i]))
			return false;
	}return true;	
}
inline bool Out(const R &A,const R &B){
	for(register int i=0;i<3;i++){
		if(A.mx[i]<B.mn[i]||A.mn[i]>B.mx[i])
			return true;
	}return false;		
}
int z=0;
struct node{
	R rc;P p;
	int sum,val;
	int l,r,f;
	void rz();
}t[maxn*2];
void node::rz(){
	sum=val;
	if(l)sum+=t[l].sum;
	if(r)sum+=t[r].sum;
}
int D;
bool cmp(P A,P B){
	return A[D]!=B[D]?A[D]<B[D]:A<B;
}
map<P,int>M;
int ss=0;
int build(int l,int r,int d){
	int x=++z;D=d;
	int mid=(l+r)>>1;
	nth_element(p+l,p+mid,p+r+1,cmp);
	t[x].p=p[mid];t[x].rc=R(t[x].p);M[t[x].p]=++ss;
	if(l<mid)t[x].l=build(l,mid-1,(d==2)?0:d+1),t[x].rc=t[x].rc+t[t[x].l].rc,t[t[x].l].f=x;
	if(r>mid)t[x].r=build(mid+1,r,(d==2)?0:d+1),t[x].rc=t[x].rc+t[t[x].r].rc,t[t[x].r].f=x;
	return x;
}
void Add(int x,P p,int d){
	x=M[p];
	t[x].val+=d;
	while(x){
		t[x].sum+=d;
		x=t[x].f;
	}	
}
int Q(int x,R rc){
	if(In(t[x].rc,rc))return t[x].sum;
	if(Out(t[x].rc,rc))return 0;
	if(!t[x].sum)return 0;
	int ans=0;
	if(In(t[x].p,rc))ans+=t[x].val;
	if(t[x].l)ans+=Q(t[x].l,rc);
	if(t[x].r)ans+=Q(t[x].r,rc);
	return ans;
}
stack<P>ad;
struct qes{	
	int ty;P p;R rc;
}qe[maxn*2];
int psz;
int main(){
	freopen("bzoj3290.in","r",stdin);
	n=in();
	for(int i=1;i<=n;i++)p[i][0]=in(),p[i][1]=in(),p[i][2]=in(),_p[i]=p[i];
	psz=n;
	m=in();
	for(int i=1;i<=m;i++){
		char op[5];scanf("%s",op);
		P p;R rc;
		if(op[0]=='A'){
			p[0]=in();p[1]=in();p[2]=in();
			qe[i].ty=1;qe[i].p=p;
			ad.push(p);
			::p[++psz]=p;
		}else if(op[0]=='Q'){
			rc.mn[0]=in();
			rc.mn[1]=in();
			rc.mn[2]=in();
			int r=in();
			rc.mx[0]=rc.mn[0]+r;
			rc.mx[1]=rc.mn[1]+r;
			rc.mx[2]=rc.mn[2]+r;
			qe[i].ty=0;
			qe[i].rc=rc;
		}else{
			qe[i].ty=-1;
			qe[i].p=ad.top();
			ad.pop();
		}
	}
	build(1,psz,0);
	for(int i=1;i<=n;i++){
		D=2;
		Add(1,_p[i],1);	
	}
	for(int i=1;i<=m;i++){
		int ty=qe[i].ty;
		if(ty==1){
			D=2;
			Add(1,qe[i].p,1);
		}else if(ty==0){
			printf("%d\n",Q(1,qe[i].rc));
		}else{
			D=2;
			Add(1,qe[i].p,-1);			
		}
	}
	return 0;
}
