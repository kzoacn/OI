#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
int dcmp(double x){return (x>eps)-(x<-eps);}
double a[233][233];
void pivot(int l,int e){
	for(int i=0;i<=n;i++)if(i!=e)
		a[l][i]/=a[l][e];
	a[l][e]=1/a[l][e];
	for(int i=0;i<=m;i++)if(i!=l){
		if(!dcmp(a[i][e]))continue;
		for(int j=0;j<=n;j++)if(j!=e)
			a[i][j]-=a[i][e]*a[l][j];			
		a[i][e]*=-a[l][e];		
	}
}

int main(){
	
	return 0;
}
