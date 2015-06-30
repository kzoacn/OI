#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int a[maxn],n,m;
int nxt(int x,int l,int ty){
	if(ty==1){
		int nx=upper_bound(a+1,a+1+n,a[x]+l)-a-1;
		return nx;	
	}else{
		int nx=lower_bound(a+1,a+1+n,a[x]-l)-a;
		return nx;
	}
}
int Q(int x,int l,int ty){
	if(x==1&&ty==-1)ty=1;
	if(x==n&&ty==1)ty=-1;
	int nx=nxt(x,l,ty);
	int d=abs(a[x]-a[nx]);
	int nxx=nxt(nx,l-d,-ty);
	if(x==nxx){
		if(!d)return x;
		return Q(x,l%(2*d),ty);
	}else return Q(nx,l-d,-ty);
}
/*
int calc(int id,int len,int dir){
    int nex=getnext(id,len,dir),nex2=getnext(nex,len-abs(a[id]-a[nex]),!dir);
    if(nex2==id){
        int sun=2*abs(a[id]-a[nex]);
        if(sun==0)return id;
        else return calc(id,len%sun,dir);
    }else return calc(nex,len-abs(a[id]-a[nex]),!dir);
}
*/
int ord[maxn],mp[maxn];
bool cmp(int x,int y){return a[x]<a[y];}
int main(){
	scanf("%d%d",&n,&m);
	if(n==1){while(m--)puts("1");return 0;}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),ord[i]=i;
	sort(ord+1,ord+1+n,cmp);
	for(int i=1;i<=n;i++)mp[ord[i]]=i;
	sort(a+1,a+1+n);
	while(m--){
		int x,l;scanf("%d%d",&x,&l);
		x=mp[x];
		printf("%d\n",ord[Q(x,l,1)]);
	}
	return 0;
}
