#include<cmath>
#include<cstdio>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long 
#define inf 1000000000
#define mod 1000000007
#define sqr(x) x*x
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll A,B,C,ans;
int F,n,m,rt;
struct P{
	int d[2],mx[2],mn[2],v,l,r;
	ll sum;
	int& operator[](int x){
		return d[x];
	}
	friend bool operator<(P a,P b){
		return a[F]<b[F];
	}
}p[50005];
bool check(int x,int y)
{
	return A*x+B*y<C;
}
int cal(P x)
{
	int tmp=0;
	tmp+=check(x.mn[0],x.mn[1]);
	tmp+=check(x.mx[0],x.mn[1]);
	tmp+=check(x.mn[0],x.mx[1]);
	tmp+=check(x.mx[0],x.mx[1]);
	return tmp;
}
struct kd{
	P t[50005];
	void update(int k){
		int l=t[k].l,r=t[k].r;
		for(int i=0;i<2;i++)
		{
			t[k].mn[i]=t[k].mx[i]=t[k][i];
			if(l)t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
			if(r)t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
			if(l)t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
			if(r)t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
		}
		t[k].sum=t[k].v+t[l].sum+t[r].sum;
	}
	int build(int l,int r,int now){
		F=now;int mid=(l+r)>>1;
		nth_element(p+l,p+mid,p+r+1);
		t[mid]=p[mid];
		if(l<mid)t[mid].l=build(l,mid-1,now^1);
		if(r>mid)t[mid].r=build(mid+1,r,now^1);
		update(mid);
		return mid;
	}
	void query(int k){
		int l=t[k].l,r=t[k].r;
		if(check(t[k][0],t[k][1]))ans+=t[k].v;
		int tl=0,tr=0;
		if(l)tl=cal(t[l]);
		if(r)tr=cal(t[r]);
		if(tl==4)ans+=t[l].sum;
		else if(tl)query(l);
		if(tr==4)ans+=t[r].sum;
		else if(tr)query(r);
	}
}kd;
int main()
{
	freopen("bzoj2850.in","r",stdin);
	n=read();m=read();
	for(int i=1;i<=n;i++)
		p[i][0]=read(),p[i][1]=read(),p[i].v=read();
	rt=kd.build(1,n,0);
	while(m--)
	{
		A=read(),B=read(),C=read();
		ans=0;
		kd.query(rt);
		printf("%lld\n",ans);
	}
	return 0;
}
