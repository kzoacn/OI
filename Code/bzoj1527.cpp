#include<bits/stdc++.h>
using namespace std;
const int maxn=25010;
typedef double DB;
int dcmp(double x){return (x>1e-8)-(x<-1e-8);}
struct P{
	DB x,y;
	P(DB x=0,DB y=0):x(x),y(y){}
	P operator+(P o){return P(x+o.x,y+o.y);}
	P operator-(P o){return P(x-o.x,y-o.y);}
	P operator/(DB p){return P(x/p,y/p);}
	bool operator<(P o)const{return dcmp(x-o.x)?dcmp(x-o.x)<0:dcmp(y-o.y)<0;}
}pk[maxn],p[maxn],A,B,C,D,AC,BD;
int n,T;
set<P>S;
double a[4][5];
void Gauss(){
	for(int i=0;i<4;i++){
		int r=i;
		for(int j=i;j<4;j++)if(fabs(a[r][i])<fabs(a[j][i]))swap(r,j);
		for(int j=i;j<=4;j++)swap(a[r][j],a[i][j]);
		if(!dcmp(a[i][i]))continue;
		for(int j=i+1;j<4;j++){
			double t=a[j][i]/a[i][i];
			for(int k=i;k<=4;k++)
				a[j][k]-=t*a[i][k];
		}
	}for(int i=3;i>=0;i--){
		for(int j=i+1;j<4;j++)
			a[i][4]-=a[i][j]*a[j][4];
		a[i][4]/=a[i][i];
	}
}
P trans(P p){
	return P(p.x*a[0][4]+p.y+a[1][4],p.x*a[2][4]+p.y+a[3][4]);
}
bool check(){
	a[0][0]=A.x;a[0][1]=A.y;a[0][2]=0;a[0][3]=0;a[0][4]=B.x;
	a[1][0]=0;a[1][1]=0;a[1][2]=A.x;a[1][3]=A.y;a[1][4]=B.y;
	a[2][0]=C.x;a[2][1]=C.y;a[2][2]=0;a[2][3]=0;a[2][4]=D.x;
	a[3][0]=0;a[3][1]=0;a[3][2]=C.x;a[3][3]=C.y;a[3][4]=D.y;
	
	for(int i=0;i<4;i++)for(int j=0;j<=4;j++)printf("%.2lf%c",a[i][j]," \n"[j==4]);
	
	Gauss();
	for(int i=1;i<=n;i++){
		P np=trans(p[i]);
		if(!S.count(np))
			return false;
	}return true;
}
void sol(){
	scanf("%*d");B=P();
	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y),B=B+p[i];
	B=B/n;C=pk[1];
	for(int i=1;i<=n;i++){
		D=p[i];
		if(check()){
			puts("TAK");
			return;
		}
	}puts("NIE");
}
int main(){
	freopen("bzoj1527.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&pk[i].x,&pk[i].y),S.insert(pk[i]),A=A+pk[i];
	A=A/n;
	scanf("%d",&T);
	while(T--)sol();
	return 0;
}
