#include<bits/stdc++.h>
#define next(i) (i+1<=n?i+1:1)
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
struct point{
	LL x,y;
	point(LL x=0,LL y=0):x(x),y(y){}
	point operator+(point oth){return point(x+oth.x,y+oth.y);}
	point operator-(point oth){return point(x-oth.x,y-oth.y);}
	LL operator*(point oth){return x*oth.y-y*oth.x;}
	LL operator^(point oth){return x*oth.x+y*oth.y;}
	double rad(){
		double r=atan2(y,x);
		return r;
	}
	LL len(){return x*x+y*y;}
}p[maxn];
bool cmp(point A,point B){
	return A.rad()<B.rad();
}
bool half(point A,point B){
	if(A*B>0)return 1;
	if(A*B<0)return 0;
	if((A^B)>=0)return 1;
	return 0;
}
int n;
int dcmp(double x){return (x>1e-8)-(x<-1e-8);}
int main(){
	freopen("bzoj1278.in","r",stdin);
	scanf("%d",&n);
	int m=0;
	for(int i=1;i<=n;i++){
		int x,y;scanf("%d%d",&x,&y);
		if(x||y)m++,p[m].x=x,p[m].y=y;
	}n=m;
	sort(p+1,p+1+n,cmp);
	m=1;
	for(int i=2;i<=n;i++){
		if(!dcmp(p[m].rad()-p[i].rad()))p[m]=p[m]+p[i];
		else p[++m]=p[i];
	}n=m;
	LL ans=0;point cur=p[1];
	for(int i=1,j=2;i<=n;){
		ans=max(ans,cur.len());
		while(i!=j&&half(p[i],p[j]))
			cur=cur+p[j],j=next(j);ans=max(ans,cur.len());
		cur=cur-p[i];
		i++;if(i==j)cur=p[i],j=next(j);
	}printf("%lld.000\n",ans);
	return 0;
}
