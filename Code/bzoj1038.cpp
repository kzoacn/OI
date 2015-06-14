#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
const double pi=acos(-1);
int n;
struct point{
	double x,y;
	point(double x=0,double y=0):x(x),y(y){}
	point operator-(point o){return point(x-o.x,y-o.y);}
	point operator+(point o){return point(x+o.x,y+o.y);}
	point operator*(double o){return point(x*o,y*o);}
	double operator*(point o){return x*o.y-y*o.x;}
	double operator^(point o){return x*o.x+y*o.y;}
};
struct line{
	point p,v;
	double k;
	line(){}
	line(point p,point v,double k=0):p(p),v(v),k(k){}
	void get(){k=atan2(v.y,v.x);if(k<0)k+=2*pi;}
	bool operator<(line o)const{return k<o.k;}
	point operator*(line o){
		point u=p-o.p;
		double t=(o.v*u)/(v*o.v);
		return p+v*t;
	}
	double get(double x){return }
}l[maxn];
int dcmp(double x){return (x>1e-7)-(x<-1e-7);}
bool Onleft(point p,line l){
	return dcmp((p-l.p)*l.v)>=0;
}
deque<line>dq;
int main(){	
	static double _x[maxn],_y[maxn];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf",&_x[i]);
	for(int i=1;i<=n;i++)scanf("%lf",&_y[i]);
	int m=0;
	l[m++]=line(point(0,0),point(1,0),0);
	l[m++]=line(point(1e7,0),point(0,1),1e9);
	l[m++]=line(point(1e7,1e7),point(-1,0),0);
	l[m++]=line(point(0,1e7),point(0,-1),-1e9);
	for(int i=1;i<n;i++){
		line L;L.p=point(_x[i],_y[i]);
		L.v=_y[i]<=_y[i+1]?point(_x[i+1]-_x[i],_y[i+1]-_y[i]):point(_x[i]-_x[i+1],_y[i]-_y[i+1]);
		L.get();l[m++]=L;
	}sort(l,l+m);
	dq.push_back(l[0]);
	dq.push_back(l[1]);
	for(int i=2;i<m;i++){
		while(dq.size()>1){
			if(dcmp(dq[dq.size()-2].k-l[i].k)){
				point p=dq[dq.size()-2]*l[i];
				if(Onleft(p,dq.back()))dq.pop_back();
			}else if(Onleft(l[i].p,dq[dq.size()-2]))
				dq.pop_back();
			dq.push_back(l[i]);
		}
		while(dq.size()>1){
			if(dcmp(dq[1].k-l[i].k)){
				point p=dq[1]*l[i];
				if(Onleft(p,dq.front()))dq.pop_front();
			}else if(Onleft(l[i].p,dq[1]))
				dq.pop_front();
			dq.push_front(l[i]);
		}	
	}
	
	return 0;
}
