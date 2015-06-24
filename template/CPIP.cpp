#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int n;
int a[maxn];
LL sum[maxn];
struct P{
	LL x,y;
	P(LL x=0,LL y=0):x(x),y(y){}
}p[maxn];
LL sqr(LL x){return x*x;}
bool byY(P a,P b){return a.y<b.y;}
LL dis2(P a,P b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
LL solve(int l,int r){
	LL d=1LL<<62;
	if(l==r)return d;
	if(l+1==r)return dis2(p[l],p[r]);
	int mid=(l+r)>>1;
	d=min(solve(l,mid),d);
	d=min(solve(mid+1,r),d);
	vector<P>tmp;
	for(int i=l;i<=r;i++)if(sqr(p[mid].x-p[i].x)<=d)
		tmp.push_back(p[i]);
	sort(tmp.begin(),tmp.end(),byY);
	for(int i=0;i<tmp.size();i++)
	for(int j=i+1;j<tmp.size()&&j-i<10;j++)
	d=min(d,dis2(tmp[i],tmp[j]));
	return d;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++)
		p[i].x=i,p[i].y=sum[i];
	cout<<solve(1,n)<<endl;
	return 0;
}
