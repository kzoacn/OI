#include<bits/stdc++.h>
using namespace std;
struct point{
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator-(point o){return point(x-o.x,y-o.y);}
	point operator+(point o){return point(x+o.x,y+o.y);}
	double operator^(point o){return x*o.x+y*o.y;}
	double operator*(point o){return x*o.y-y*o.x;}
	point operator*(double p){return point(x*p,y*p);}
	point operator/(double p){return point(x/p,y/p);}
}A,B,C,D;
double sqr(double x){return x*x;}
double length(point A){return sqrt(sqr(A.x)+sqr(A.y));}
point normal(point v){return v/length(v);}
double P,Q,R,lenAB,lenCD;
double ans=1e10;
double dis(point A,point B){return length(B-A);}
double dist(point T,point E){
	double ans=0;
	ans+=dis(T,E)/R;
	ans+=dis(E,D)/Q;
	return ans;
}
double calc(point T){
	double res=0;
	point _C=C,_D=D;
	do{
		point LL=_C+(_D-_C)/3;
		point RR=_C+(_D-_C)/3*2;
		double t1=dis(A,T)/P+dis(T,LL)/R+dis(LL,D)/Q;
		double t2=dis(A,T)/P+dis(T,RR)/R+dis(RR,D)/Q;	
		if(t1>t2)
			_C=LL;
		else _D=RR;
	}while(dis(_C,_D)>1e-4);
	res=dis(A,T)/P+dis(T,_C)/R+dis(_C,D)/Q;
	ans=min(ans,res);
	return res;
}
int main(){
	scanf("%lf%lf",&A.x,&A.y);
	scanf("%lf%lf",&B.x,&B.y);
	scanf("%lf%lf",&C.x,&C.y);
	scanf("%lf%lf",&D.x,&D.y);
	scanf("%lf%lf%lf",&P,&Q,&R);
	lenAB=length(B-A);
	lenCD=length(D-C);
	double l=0,r=lenAB;
	int k=1000;
	point _A=A,_B=B;
    do{
//		double mid1=l+(r-l)/3;
//		double mid2=l+(r-l)/3*2;	
		point T1=_A+(_B-_A)/3;
		point T2=_A+(_B-_A)/3*2;
		if(calc(T1)<calc(T2))
			_B=T2;
		else _A=T1;
	}while(dis(_A,_B)>1e-4);
	cout<<fixed<<setprecision(2)<<ans<<endl;
	return 0;
}
