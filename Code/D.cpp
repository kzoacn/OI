#include<bits/stdc++.h>
using namespace std;
double sqr(double x){return x*x;}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		double T1,T2,t1,t2;
		scanf("%lf%lf%lf%lf",&T1,&T2,&t1,&t2);
		if(T1<T2)swap(T1,T2),swap(t1,t2);
		
		double S=T1*T2;
		if(t1<=T2)
			S-=sqr(T2-t1)/2;
		
		if(T1-t2>=0){	
			if(T1-t2<=T2)
				S-=sqr(T1-t2)/2;
			else S-=sqr(T2)/2,S-=T2*(T1-t2-T2);
		}
		if(S<=0)S=0;
		printf("%.7lf\n",S/T1/T2);
	}
}
