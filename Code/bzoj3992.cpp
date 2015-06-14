#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1004535809;
const int maxn=16405;
int n,m,S,g,N;
bool ok(int x){
	static int vis[maxn];
	int cur=1;
	for(int i=0;i<m-1;i++){
		if(vis[cur]==x)return 0;
		vis[cur]=x;
		cur=cur*x%m;
	}return 1;
}
int idx[maxn];
LL pw(LL x,LL k,LL p=mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;	
	}return ans;
}
void FNT(int a[],int n,int ty){
	static LL tmp[maxn];
	if(n==1)return ;
	for(int i=0;i<n;i+=2)
		tmp[i>>1]=a[i],tmp[i+n>>1]=a[i+1];
	for(int i=0;i<n;i++)a[i]=tmp[i];
	int *l=a,*r=a+(n>>1);
	FNT(l,n>>1,ty);FNT(r,n>>1,ty);
	LL w=1,wn=pw(3,(LL)ty*(mo-1)/n%(mo-1),mo);
	for(int i=0;i<n/2;i++,w=w*wn%mo)
		tmp[i]=(l[i]+(LL)w*r[i]%mo)%mo,tmp[i+n/2]=(l[i]+mo-(LL)w*r[i]%mo)%mo;
	for(int i=0;i<n;i++)a[i]=tmp[i];
}
struct Poly{
	int a[maxn];
	int at(int x)const{return a[x];}
	void clear(){memset(a,0,sizeof a);}
	int& operator[](int x){return a[x];}
	Poly(){}
}a,tmp,res;

Poly operator*(const Poly &ls,const Poly &rs){
	static int a[maxn],b[maxn];tmp.clear();
	for(int i=0;i<N;i++)a[i]=ls.at(i),b[i]=rs.at(i);
	tmp.clear();
	FNT(a,N,1);
	FNT(b,N,1);
	for(int i=0;i<N;i++)
	tmp[i]=(LL)a[i]*b[i]%mo;
	FNT(tmp.a,N,mo-2);
	for(int i=0;i<m-1;i++)
	tmp[i]=(tmp[i]+tmp[i+m-1])%mo,tmp[i+m-1]=0;
	LL inv=pw(N,mo-2,mo);
	for(int i=0;i<m-1;i++)tmp[i]=tmp[i]*inv%mo;
	return tmp;
}
Poly x;
Poly pw(const Poly &_x,LL k){
	res.clear();res[0]=1;x=_x;
	for(;k;k>>=1){
		if(k&1)res=res*x;
		x=x*x;
	}return res;
}
int main(){
	int x;
	scanf("%d%d%d%d",&n,&m,&x,&S);
	for(int i=2;i<m;i++)if(ok(i)){g=i;break;}
	for(int x=1,i=0;i<m-1;i++,x=x*g%m)idx[x]=i;
	for(N=1;N<m;N<<=1);N<<=1;
	for(int i=0;i<S;i++){
		int y;scanf("%d",&y);
		if(y)a[idx[y]]=1;
	}
	a=pw(a,n);
	cout<<a.at(idx[x])<<endl;
	return 0;
}
