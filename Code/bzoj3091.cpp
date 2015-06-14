#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
typedef long long LL;
LL presum[maxn],presum2[maxn];
struct info{
	LL ans,psum,ssum,sum;
	LL siz;
	info(){ans=0;psum=0;ssum=0;sum=0;siz=0;}
	info(int val){ans=psum=ssum=sum=val;siz=1;}
	void deb(){
		printf("%lld %lld %lld %lld %lld ",ans,psum,ssum,sum,siz);
	}
};
info operator+(const info &ls,const info &rs){
	info I;
	I.siz=ls.siz+rs.siz;
	I.sum=ls.sum+rs.sum;
	I.psum=ls.psum+ls.siz*rs.sum+rs.psum;
	I.ssum=ls.ssum+rs.siz*ls.sum+rs.ssum;;
	I.ans=ls.ans+rs.ans+(ls.psum*rs.siz+rs.ssum*ls.siz);
	return I;
}
info operator+(LL d,const info &rs){
	info I=rs;
	LL n=rs.siz;
	I.sum+=rs.siz*d;
	I.psum+=d*presum[n];
	I.ssum+=d*presum[n];
	I.ans+=d*presum2[n];
	return I;
}
struct node{
	info I;
	int add,rev,val;
	node *c[2],*f;
	node *rz(){
		I=info(val);
		if(c[0])I=c[0]->I+I;
		if(c[1])I=I+c[1]->I;
		return this;
	}
	void makerv(){
		rev^=1;
		swap(I.psum,I.ssum);
		swap(c[0],c[1]);
	}
	void pd(){
		if(rev){
			if(c[0])c[0]->makerv();
			if(c[1])c[1]->makerv();
			rev=0;
		}
		if(add){
			if(c[0])c[0]->add+=add,c[0]->val+=add,c[0]->I=add+c[0]->I;
			if(c[1])c[1]->add+=add,c[1]->val+=add,c[1]->I=add+c[1]->I;
			add=0;		
		}
	}
	bool d(){return this==f->c[1];}
	bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
	void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
}nd[maxn];
void rot(node *x){
	node *y=x->f;if(!y->rt())y->f->pd();
	y->pd();x->pd();bool d=x->d();
	y->sets(x->c[!d],d);
	if(!y->rt())y->f->sets(x,y->d());
	else x->f=y->f;
	x->sets(y,!d);
}
void splay(node *x){
	while(!x->rt()){
		if(x->f->rt())rot(x);
		else if(x->d()==x->f->d())rot(x->f),rot(x);
		else rot(x),rot(x);
	}
}
node *access(node *x){
	node *y=0;
	for(;x;x=x->f){
		splay(x);
		x->sets(y,1);
		y=x;
	}return y;
}
void makert(node *x){
	access(x)->makerv();
	splay(x);
}
bool connect(node *x,node *y){
	makert(x);
	access(y);
	splay(y);
	while(!x->rt())x=x->f;
	return x==y;	
}
node *findp(node *x){
	access(x);
	splay(x);
	x=x->c[0];
	while(x&&x->c[1])x=x->c[1];
	return x;	
}
void link(node *u,node *v){
	if(connect(u,v))return;
	makert(u);
//	splay(u);
	u->f=v;
	access(u);
}
void cut(node *u,node *v){
	makert(u);
	if(findp(v)!=u)return;
	access(v);splay(v);
	v->c[0]=u->f=0;v->rz();
}
node *expose(node *u,node *v){
	makert(u);
	access(v);
	splay(v);
	return v;
}
void Q(node *u,node *v){
	if(!connect(u,v))return (void)puts("-1");
	info I=expose(u,v)->I;
	LL son=I.ans;
	LL mom=presum[I.siz];
	LL d=__gcd(son,mom);
	son/=d;mom/=d;
	printf("%lld/%lld\n",son,mom);	
}
void A(node *u,node *v,int d){
	if(!connect(u,v))return ;
	node *w=expose(u,v);
	w->val+=d;
	w->add+=d;
	w->pd();
	w->rz();
}
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m;
#define o(x) (x?x-nd:0)
void deb(){
	for(int i=1;i<=n;i++){
		printf("id:%d c[0]:%d c[1]:%d f:%d rev:%d val:%d ",i,o(nd[i].c[0]),o(nd[i].c[1]),o(nd[i].f),nd[i].rev,nd[i].val);
		nd[i].I.deb();
		puts("");
	}puts("");
}
int main(){
//	freopen("bzoj3091.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=n;i++)presum[i]=presum[i-1]+i;
	for(int i=1;i<=n;i++)presum2[i]=presum2[i-1]+presum[i];
	for(int i=1;i<=n;i++)nd[i].val=in(),nd[i].rz();
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		link(nd+u,nd+v);
	}
	while(m--){
		int ty=in();
		int u=in(),v=in();
		if(ty==1){
			cut(nd+u,nd+v);
		}else if(ty==2){
			link(nd+u,nd+v);
		}else if(ty==3){
			A(nd+u,nd+v,in());
		}else{
			Q(nd+u,nd+v);
		}
	}
	return 0;
}
