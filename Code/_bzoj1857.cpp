#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#define inf 1000000000
#define eps 1e-3
using namespace std;
int ax,ay,bx,by;
int cx,cy,dx,dy;
int p,q,r;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
double dis(double x1,double y1,double x2,double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double cal(double x,double y)
{
	double lx=cx,ly=cy,rx=dx,ry=dy;
	double x1,y1,x2,y2,t1,t2;
	while(fabs(rx-lx)>eps||fabs(ry-ly)>eps)
	{
		x1=lx+(rx-lx)/3;y1=ly+(ry-ly)/3;
		x2=lx+(rx-lx)/3*2;y2=ly+(ry-ly)/3*2;
		t1=dis(ax,ay,x,y)/p+dis(x,y,x1,y1)/r+dis(x1,y1,dx,dy)/q;
		t2=dis(ax,ay,x,y)/p+dis(x,y,x2,y2)/r+dis(x2,y2,dx,dy)/q;
		if(t1>t2){lx=x1;ly=y1;}
		else {rx=x2;ry=y2;}
	}
	return  dis(ax,ay,x,y)/p+dis(x,y,lx,ly)/r+dis(lx,ly,dx,dy)/q;
}
int main()
{
    ax=read(),ay=read(),bx=read(),by=read();
	cx=read(),cy=read(),dx=read(),dy=read();
	p=read();q=read();r=read();
	double lx=ax,ly=ay,rx=bx,ry=by;
	double x1,y1,x2,y2,t1,t2;
	while(fabs(rx-lx)>eps||fabs(ry-ly)>eps)
	{
		x1=lx+(rx-lx)/3;y1=ly+(ry-ly)/3;
		x2=lx+(rx-lx)/3*2;y2=ly+(ry-ly)/3*2;
		t1=cal(x1,y1);t2=cal(x2,y2);
		if(t1>t2){lx=x1;ly=y1;}
		else {rx=x2;ry=y2;}
	}
	printf("%.2lf\n",cal(lx,ly));
	return 0;
}
