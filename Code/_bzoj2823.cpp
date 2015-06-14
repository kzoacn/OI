#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cmath>
#define eps 1e-6
#define inf 1000000000
#define pa pair<int,int>
#define ll long long 
using namespace std;
int n;
double r;
struct P{
	double x,y;
}p[1000005],o;
//ax^2-bx^2-(2ax-2bx)x+ay^2-by^2-(2ay-2by)y=0
//ax^2-cx^2-(2ax-2cx)x+ay^2-cy^2-(2ay-2cy)y=0
//==>
//ax^2-bx^2+ay^2-by^2=(2ax-2bx)x+(2ay-2by)y
//ax^2-cx^2+ay^2-cy^2=(2ax-2cx)x+(2ay-2cy)y
//==>
//l1=r1x+r2y
//l2=r3x+r4y
double sqr(double x)
{
	return x*x;
}
double dis(P a,P b)
{
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
P getcen(P a,P b,P c)
{
	double x,y;
	double ax=sqr(a.x),ay=sqr(a.y),bx=sqr(b.x),by=sqr(b.y),cx=sqr(c.x),cy=sqr(c.y);
	double l1=ax-bx+ay-by,l2=ax-cx+ay-cy;
	double r1=2*a.x-2*b.x,r2=2*a.y-2*b.y,r3=2*a.x-2*c.x,r4=2*a.y-2*c.y;
	x=(l1-r2/r4*l2)/(r1-r2/r4*r3);
	y=(l1-r1/r3*l2)/(r2-r1/r3*r4);
	if(r4==0)x=(a.x+c.x)/2;
	if(r3==0)y=(a.y+c.y)/2;
	return (P){x,y};
}
P getcen(P a,P b)
{
	return (P){(a.x+b.x)/2,(a.y+b.y)/2};
}
int main()
{
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&p[i].x,&p[i].y);
		swap(p[i],p[rand()%i+1]);
	}
	o=p[1];
	for(int i=1;i<=n;i++)
	{
		if(dis(o,p[i])<=r+eps)continue;
		o=getcen(p[1],p[i]);r=dis(p[i],o);
		for(int j=1;j<i;j++)
		{
			if(dis(o,p[j])<=r+eps)continue;
			o=getcen(p[i],p[j]);r=dis(p[i],o);
			for(int k=1;k<j;k++)
			{
				if(dis(o,p[k])<=r+eps)continue;
				o=getcen(p[i],p[j],p[k]);r=dis(p[i],o);
			}
		}
	}
	printf("%.2lf %.2lf %.2lf\n",o.x,o.y,r);
	return 0;
}
