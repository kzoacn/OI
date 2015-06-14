/*
poj 2451 Uyuw's Concert - ????

???????


*/
#include<stdio.h>
#include<math.h>
#include <algorithm>
using namespace std;

const double eps=1e-10;
struct point
{
	double x,y;
	point(){}
	point(double a,double b):x(a),y(b){}
}jiao[20000+10];

struct line
{
	point s,e;
	double angle;
}xian[20000+10];
int n;
int yong;
/////
//???????,????????????!
//????????????(???????????!)
point mo_intersection(point u1,point u2,point v1,point v2)
{
    point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
             /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
double mo_xmult(point p2,point p0,point p1)//p1?p2????,??????
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

//??????
double mo_area_polygon(point *dian,int n)
{
	int i;
	point yuan;
	yuan.x=yuan.y=0;
	double ret=0;
	for(i=0;i<n;++i)
	{
		ret+=mo_xmult(dian[(i+1)%n],yuan,dian[i]);
	}
	if(ret<0) ret=-ret;
	return ret/2;
}
bool mo_ee(double x,double y)
{
	double ret=x-y;
	if(ret<0) ret=-ret;
	if(ret<eps) return 1;
	return 0;
}
bool mo_gg(double x,double y)  {   return x > y + eps;} // x > y   
bool mo_ll(double x,double y)  {   return x < y - eps;} // x < y   
bool mo_ge(double x,double y) {   return x > y - eps;} // x >= y   
bool mo_le(double x,double y) {   return x < y + eps;}     // x <= y   

bool mo_HPI_cmp(const line& a,const line& b)
{
	if(mo_ee(a.angle,b.angle))
	{
		return mo_gg( mo_xmult(b.e,a.s,b.s),0);
	}else
	{
		return mo_ll(a.angle,b.angle);
	}
}
int mo_HPI_dq[20000+10];
bool mo_HPI_isout(line cur,line top,line top_1)
{
	point jiao=mo_intersection(top.s,top.e,top_1.s,top_1.e);
	return mo_ll( mo_xmult(cur.e,jiao,cur.s),0);
}
int mo_HalfPlaneIntersect(line *xian,int n,point *jiao)
{
	int i,j,ret=0;
	sort(xian,xian+n,mo_HPI_cmp);
	for (i = 0, j = 0; i < n; i++)
    {
		if (mo_gg(xian[i].angle,xian[j].angle)) //?????,??????????
		{
			xian[++j] = xian[i];
		}
	}
	n=j+1;
	mo_HPI_dq[0]=0;
	mo_HPI_dq[1]=1;
	int top=1,bot=0;
	for (i = 2; i < n; i++) {
        //???????????????????,??
        while (top > bot && mo_HPI_isout(xian[i], xian[mo_HPI_dq[top]], xian[mo_HPI_dq[top-1]])) 
		{
			top--;
		}
        /*???????????,?????????????,??????????while????,
          ?????????????,???????????,??????????,????
        */
        while (top > bot && mo_HPI_isout(xian[i], xian[mo_HPI_dq[bot]], xian[mo_HPI_dq[bot+1]])) 
		{
			bot++;
		}
        mo_HPI_dq[++top] = i; //???????
    }
    //???????????????????????,????????????,????
    while (top > bot && mo_HPI_isout(xian[mo_HPI_dq[bot]], xian[mo_HPI_dq[top]], xian[mo_HPI_dq[top-1]])) top--;
    //???????????????????????,????????????,????
    while (top > bot && mo_HPI_isout(xian[mo_HPI_dq[top]], xian[mo_HPI_dq[bot]], xian[mo_HPI_dq[bot+1]])) bot++;
    mo_HPI_dq[++top] = mo_HPI_dq[bot]; //??????????????,???????
    for (ret = 0, i = bot; i < top; i++, ret++)
	{
		jiao[ret]=mo_intersection(xian[mo_HPI_dq[i+1]].s,xian[mo_HPI_dq[i+1]].e,xian[mo_HPI_dq[i]].s,xian[mo_HPI_dq[i]].e);
	}
	return ret;
}
/////
void addl(point a,point b)
{
	xian[yong].s=a;
	xian[yong].e=b;
	xian[yong].angle=atan2(b.y-a.y,b.x-a.x);
	yong++;
}
int main()
{
	int i;
	while(scanf("%d",&n)!=EOF)
	{
		point a,b;
		yong=0;
		for(i=0;i<n;++i)
		{
			scanf("%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y);
			addl(a,b);
		}
		addl(point(0,0),point(10000,0));
		addl(point(10000,0),point(10000,10000));
		addl(point(10000,10000),point(0,10000));
		addl(point(0,10000),point(0,0));
		int ret=mo_HalfPlaneIntersect(xian,n+4,jiao);
		double area=mo_area_polygon(jiao,ret);
		printf("%.1lf\n",area);
	}
	return 0;
}
