#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int n,m,pre[maxn],nxt[maxn],tmp[maxn];
struct point{int w,x,y,z;}P[maxn];
bool cmpw(point a,point b){return a.w<b.w;}
bool cmpx(point a,point b){return a.x<b.x;}
bool cmpy(point a,point b){return a.y<b.y;}
bool cmpz(point a,point b){return a.z<b.z;}
bool (*cmp[4])(point a,point b) = {cmpw,cmpx, cmpy, cmpz};
int C(int l0,int r0,int l1,int r1){
	if(l0<=l1&&r0>=r1)return 2;
	if((l0<=l1&&r0>=l1)||(l0<=r1&&r0>=r1)||(l1<=l0&&r1>=r0))return 1;
	return 0;
}
struct node{
	node *c[2];
	int mn[4],mx[4],size;
	node(){c[0]=c[1]=0;for(int i=0;i<4;i++)mn[i]=mx[i]=0;size=0;}
	node(point p){
		c[0]=c[1]=0;size=1;
		mn[0]=mx[0]=p.w;
		mn[1]=mx[1]=p.x;
		mn[2]=mx[2]=p.y;
		mn[3]=mx[3]=p.z;
	}
	void rz(){
		for(int i=0;i<4;i++)mn[i]=1e9,mx[i]=0;
		if(c[0])for(int i=0;i<4;i++)mn[i]=min(mn[i],c[0]->mn[i]),mx[i]=max(mx[i],c[0]->mx[i]);
		if(c[1])for(int i=0;i<4;i++)mn[i]=min(mn[i],c[1]->mn[i]),mx[i]=max(mx[i],c[1]->mx[i]);
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0);
	}
	int operator*(node o){
		int cov=1,cro=0;
		for(int i=0;i<4;i++){
			int res=C(mn[i],mx[i],o.mn[i],o.mx[i]);
			if(res!=2)cov=0;
			if(res)cro++;
		}if(cov)return 2;
		if(cro==4)return 1;
		return 0;
	}
}pool[maxn<<2],*cur=pool+1,*root=pool;
node *newnode(){return cur++;}
void build(node *t,int l,int r,int d){
	if(l==r){*t=node(P[l]);return;}
	nth_element(P+l,P+(l+r)/2,P+r+1,cmp[d]);
	if(!t->c[0])t->c[0]=newnode();
	if(!t->c[1])t->c[1]=newnode();
	build(t->c[0],l,(l+r)/2,(d+1)%4);
	build(t->c[1],(l+r)/2+1,r,(d+1)%4);
	t->rz();
}
int Qsum(node *t,node C){
	if(C* *t==2)return t->size;
	int ans=0;
	if(t->c[0]&&C* *t->c[0])
		ans+=Qsum(t->c[0],C);
	if(t->c[1]&&C* *t->c[1])
		ans+=Qsum(t->c[1],C);
	return ans;	
}
int a[maxn];
int main(){
	n=getint();m=getint();int mx;
	for(int i=1;i<=n;i++)a[i]=getint();mx=*max_element(a+1,a+1+n);
	for(int i=1;i<=n;i++)pre[i]=tmp[a[i]],tmp[a[i]]=i;
	for(int i=1;i<=n;i++)tmp[i]=n+1;
	for(int i=n;i>=1;i--)nxt[i]=tmp[a[i]],tmp[a[i]]=i;
	for(int i=1;i<=n;i++)P[i]=(point){pre[i],nxt[i],i,a[i]};
	build(root,1,n,2);
	int lans=0;
	while(m--){
		int _l=(getint()+lans)%n+1,_r=(getint()+lans)%n+1;
		if(_l>_r)swap(_l,_r);
		int l=0,r=mx+1;
		while(l<r){
			int mid=(l+r)>>1;
			node C;
			C.mn[0]=0;C.mx[0]=_l-1;
			C.mn[1]=_r+1;C.mx[1]=n+1;
			C.mn[2]=_l;C.mx[2]=_r;
			C.mn[3]=mid;C.mx[3]=n+1;
			int res=Qsum(root,C);
			if(res)
				l=mid+1;
			else r=mid;
		}node C;
		C.mn[0]=0;C.mx[0]=_l-1;
		C.mn[1]=_r+1;C.mx[1]=n+1;
		C.mn[2]=_l;C.mx[2]=_r;
		C.mn[3]=l-1;C.mx[3]=n+1;
		int res=Qsum(root,C);
		printf("%d\n",lans=(res==1?l-1:0));		
		lans=0;
	}cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	return 0;
}
