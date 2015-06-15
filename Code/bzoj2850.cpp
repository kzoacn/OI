#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
typedef long long LL;
int in(){
	int f=1;
	int r=0;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m;
struct point{
	int x,y,h;
	point(int x=0,int y=0):x(x),y(y){}
	int& operator[](int s){return s==0?x:y;}
}p[maxn];
struct rec{
	int mn[2],mx[2];
	rec(){}
	rec(point p){mn[0]=mx[0]=p[0];mn[1]=mx[1]=p[1];}
};
rec operator+(rec A,rec B){
	for(int i=0;i<2;i++){
		A.mn[i]=min(A.mn[i],B.mn[i]);
		A.mx[i]=max(A.mx[i],B.mx[i]);
	}return A;
}
struct node{
	rec R;point p;
	LL sum;
	int l,r;
	void rz();
}t[maxn];
void node::rz(){
	sum=p.h;R=rec(p);
	if(l)sum+=t[l].sum,R=R+t[l].R;
	if(r)sum+=t[r].sum,R=R+t[r].R;
}
int D,z;
bool cmp(point A,point B){
	if(D)return A.y<B.y;
	return A.x<B.x;
}
int build(int l,int r,int d){
	int mid=(l+r)>>1;D=d;int x=++z;
	nth_element(p+l,p+mid,p+r+1,cmp);
	t[x].p=p[mid];
	if(l<=mid-1)t[x].l=build(l,mid-1,d^1);
	if(mid+1<=r)t[x].r=build(mid+1,r,d^1);
	t[x].rz();return x;
}
LL A,B,C;
bool under(point p){
	return (LL)A*p.x+(LL)B*p.y<(LL)C;
}
bool up(point p){
	return (LL)A*p.x+(LL)B*p.y>=(LL)C;
}
bool under(rec R){
	return under(point(R.mx[0],R.mx[1]))
			&&under(point(R.mx[0],R.mn[1]))
			&&under(point(R.mn[0],R.mx[1]))
			&&under(point(R.mn[0],R.mn[1]));
}
bool up(rec R){
	return up(point(R.mx[0],R.mx[1]))
			&&up(point(R.mx[0],R.mn[1]))
			&&up(point(R.mn[0],R.mx[1]))
			&&up(point(R.mn[0],R.mn[1]));
}
LL Q(int i){
	if(under(t[i].R))return t[i].sum;
	if(up(t[i].R))return 0;
	LL ans=0;
	if(under(t[i].p))ans+=t[i].p.h;
	if(t[i].l)ans+=Q(t[i].l);
	if(t[i].r)ans+=Q(t[i].r);
	return ans;
}
int main(){
	freopen("bzoj2850.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=n;i++)
		p[i].x=in(),p[i].y=in(),p[i].h=in();
	build(1,n,0);
	while(m--){
		A=in(),B=in(),C=in();
		printf("%lld\n",Q(1));
	}
	return 0;
}
