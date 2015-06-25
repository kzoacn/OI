#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
int dcmp(double x){return (x>eps)-(x<-eps);}
struct point{
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator-(point o){return point(x-o.x,y-o.y);}
	point operator+(point o){return point(x+o.x,y+o.y);}
	double operator*(point o){return x*o.y-y*o.x;}
	double operator^(point o){return x*o.x+y*o.y;}
	point operator*(double p){return point(x*p,y*p);}
	point operator/(double p){return point(x/p,y/p);}
	bool operator==(point o){return !dcmp(x-o.x)&&!dcmp(y-o.y);}
}O,p[int(1000001)];
double sqr(double x){return x*x;}
double dis(point a,point b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
int n;
double r;
struct line{
	point p,v;
};
point Rev(point v){return point(-v.y,v.x);}
point operator*(line A,line B){
	point u=B.p-A.p;
	double t=(B.v*u)/(B.v*A.v);
	return A.p+A.v*t;
}
point get(point a,point b){
	return (a+b)/2;
}
point get(point a,point b,point c){
	if(a==b)return get(a,c);
	if(a==c)return get(a,b);
	if(b==c)return get(a,b);	
	line ABO=(line){(a+b)/2,Rev(a-b)};
	line BCO=(line){(c+b)/2,Rev(b-c)};
	return ABO*BCO;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+1+n);
	O=p[1];r=0;
	for(int i=2;i<=n;i++){
		if(dis(p[i],O)<r+1e-6)continue;
		O=get(p[1],p[i]);r=dis(O,p[i]);
		for(int j=1;j<i;j++){
			if(dis(p[j],O)<r+1e-6)continue;
			O=get(p[i],p[j]);r=dis(O,p[i]);
			for(int k=1;k<j;k++){
				if(dis(p[k],O)<r+1e-6)continue;
				O=get(p[i],p[j],p[k]);r=dis(O,p[i]);
			}
		}
	}printf("%.2lf %.2lf %.2lf\n",O.x,O.y,r);
	return 0;
}s 
