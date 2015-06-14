#include<bits/stdc++.h>
using namespace std;
const int maxn=20010;
const double pi=acos(-1);
int n;
struct point{
	double x,y;
	point(double x=0,double y=0):x(x),y(y){}
	point operator-(point o)const{return point(x-o.x,y-o.y);}
	point operator+(point o){return point(x+o.x,y+o.y);}
	point operator*(double o){return point(x*o,y*o);}
	double operator*(point o){return x*o.y-y*o.x;}
	double operator^(point o){return x*o.x+y*o.y;}
};
int dcmp(double x){return (x>1e-10)-(x<-1e-10);}
struct line{
	point p,v;
	double k;
	line(){}
	line(point p,point v,double k=0):p(p),v(v),k(k){}
	void get(){k=atan2(v.y,v.x);if(k<0)k+=2*pi;}
	bool operator<(line o)const{
		if(dcmp(k-o.k))return k<o.k;
		else return dcmp(o.v*(p-o.p))>=0;
	}
	point operator*(line o){
		point u=p-o.p;
		double t=(o.v*u)/(v*o.v);
		return p+v*t;
	}
}l[maxn];
bool Onleft(point p,line l){
	return dcmp(l.v*(p-l.p))>0;
}
deque<line>dq;
int main(){	
	int m=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		double x_1,y_1,x_2,y_2;
		scanf("%lf%lf%lf%lf",&x_1,&y_1,&x_2,&y_2);
		l[m++]=line(point(x_1,y_1),point(x_2-x_1,y_2-y_1));l[m-1].get();
	}
	l[m++]=line(point(0,0),point(1,0));l[m-1].get();
	l[m++]=line(point(10000,0),point(0,1));l[m-1].get();
	l[m++]=line(point(10000,10000),point(-1,0));l[m-1].get();
	l[m++]=line(point(0,10000),point(0,-1));l[m-1].get();
	sort(l,l+m);
	dq.push_back(l[0]);dq.push_back(l[1]);
	for(int i=2;i<m;i++){
		while(dq.size()>1&&!Onleft(dq.back()*dq[dq.size()-2],l[i]))
			dq.pop_back();
		while(dq.size()>1&&!Onleft(dq.front()*dq[1],l[i]))
			dq.pop_front();
		dq.push_back(l[i]);
	}while(dq.size()>1&&!Onleft(dq.back()*dq[dq.size()-2],dq.front()))
		dq.pop_back();
	while(dq.size()>1&&!Onleft(dq.front()*dq[1],dq.back()))
		dq.pop_front();
	vector<point>vec;
	for(int i=0;i<dq.size();i++)vec.push_back(dq[i]*dq[(i+1)%dq.size()]);
	double ans=0;
	for(int i=1;i+1<vec.size();i++){
		ans+=(vec[i]-vec[0])*(vec[i+1]-vec[0]);
	}printf("%.1lf\n",fabs(ans/2));
	return 0;
}
