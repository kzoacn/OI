#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int seq[maxn];
LL X;
int rnd(){
	X=((LL)100000005*X+20150609)%998244353;
	return X/100;
}
struct P{
	LL x,y;
	P(LL x=0,LL y=0):x(x),y(y){}
	bool operator<(P o)const{return x<o.x||(x==o.x&&y<o.y);}
	P operator-(P o){return P(x-o.x,y-o.y);}
	LL operator*(P o){return x*o.y-y*o.x;}
	LL operator^(P o){return x*o.x+y*o.y;}
};
struct CH{
	vector<P>ch;
	void push_back(P p){
		while(ch.size()>1&&(ch.back()-ch[ch.size()-2])*(p-ch.back())>=0)ch.pop_back();
		ch.push_back(p);
	}
	void replace(LL x,LL y){
		for(int i=0;i<ch.size();i++){
			if(ch[i].x==x){
				ch.erase(ch.begin()+i,ch.begin()+i+1);
				break;
			}
		}
		ch.push_back(P(x,y));
		rebuild();
	}
	void rebuild(){
		vector<P>_ch;
		sort(ch.begin(),ch.end());
		_ch=ch;ch.clear();
		for(int i=0;i<_ch.size();i++)push_back(ch[i]);	
	}
	LL Qmax(P p){
		int l=0,r=ch.size()-1;
		LL ans=0;
		while(r-l>2){
			int mid1=l+(r-l)/3;
			int mid2=r-(r-l)/3;
			if((p^ch[mid1])>(p^ch[mid2]))
				r=mid2;
			else l=mid1;
		}for(int i=l;i<=r;i++)ans=max(ans,p^ch[i]);
		return ans;
	}
};
CH merge(CH A,CH B){
	CH C;
	for(int i=0;i<A.ch.size();i++)C.ch.push_back(A.ch[i]);
	for(int i=0;i<B.ch.size();i++)C.ch.push_back(B.ch[i]);
	C.rebuild();return C;
}
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m,z;
struct node{
	CH up,dw;
	int l,r;
}t[maxn*2];
#define lson t[i].l,l,(l+r)/2
#define rson t[i].r,(l+r)/2+1,r
#define ls t[i].l
#define rs t[i].r
void rz(int i){
	t[i].up=merge(t[ls].up,t[rs].up);
	t[i].dw=merge(t[ls].dw,t[rs].dw);
}
int build(int l,int r){
	int x=++z;
	if(l==r){
		t[x].up.push_back(P(l,seq[l]));
		t[x].dw.push_back(P(l,100000-seq[l]));
		return x;
	}
	int mid=(l+r)>>1;
	t[x].l=build(l,mid);
	t[x].r=build(mid+1,r);
	rz(x);
	return x;
}
int rev[maxn*2];
void mk(int i){
	rev[i]^=1;
	swap(t[i].up,t[i].dw);
}
void push(int i){
	if(rev[i]){
		mk(ls);mk(rs);
		rev[i]=0;
	}
}
void C(int i,int l,int r,int ps,int y){
	if(l==r){
		t[i].up.replace(ps,y);
		t[i].dw.replace(ps,100000-y);		
		return ;
	}push(i);
	if(ps<=(l+r)/2)C(lson,ps,y);
	else C(rson,ps,y);
	rz(i);
}
void R(int i,int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r){
		mk(i);
		return;
	}push(i);
	if(l0<=(l+r)/2)R(lson,l0,r0);
	if(r0>(l+r)/2)R(rson,l0,r0);
	rz(i);
}
LL Qmax(int i,int l,int r,int l0,int r0,P p){
	if(l0<=l&&r0>=r){
		return t[i].up.Qmax(p);
	}push(i);
	LL ans=0;
	if(l0<=(l+r)/2)ans=max(ans,Qmax(lson,l0,r0,p));
	if(r0>(l+r)/2)ans=max(ans,Qmax(rson,l0,r0,p));
	return ans;
}
void BF(){
	while(m--){
		char op[2];scanf("%s",op);
		if(op[0]=='C'){
			int ps=rnd()%n+1,y=rnd()%100001;
			seq[ps]=y;
		}else if(op[0]=='R'){
			int l=rnd()%n+1,r=rnd()%n+1;
			if(l>r)swap(l,r);
			for(int i=l;i<=r;i++)seq[i]=100000-seq[i];
		}else{
			int l=rnd()%n+1,r=rnd()%n+1;
			if(l>r)swap(l,r);
			int a=in(),b=in(),c=in();
			LL ans=0;
			for(int i=l;i<=r;i++)ans=max(ans,(LL)a*i+(LL)b*seq[i]+(LL)c*i*seq[i]);
			printf("%lld\n",ans);
		}
	}
}
int main(){
	freopen("B.in","r",stdin);
	n=in();m=in();X=in();
	for(int i=1;i<=n;i++)seq[i]=rnd()%100001;
	if(n<=100&&m<=100){
		BF();return 0;
	}
	build(1,n);
	while(m--){
		char op[2];scanf("%s",op);
		if(op[0]=='C'){
			int ps=rnd()%n+1,y=rnd()%100001;
			C(1,1,n,ps,y);
		}else if(op[0]=='R'){
			int l=rnd()%n+1,r=rnd()%n+1;
			if(l>r)swap(l,r);
			R(1,1,n,l,r);
		}else{
			int l=rnd()%n+1,r=rnd()%n+1;
			if(l>r)swap(l,r);
			int a=in(),b=in(),c=in();
			printf("%lld\n",Qmax(1,1,n,l,r,P(a,b)));
		}
	}
	return 0;
}
