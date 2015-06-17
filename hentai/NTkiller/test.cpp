#include<bits/stdc++.h>
using namespace std;
int phi[233],u[233],id[233],e[233],d[233],sig[233],p[233],minp[233];
void init(){
	phi[1]=u[1]=id[1]=e[1]=d[1]=1;
	
}
int f(int n){

}
int calc(int n){
	int ans=0;
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			ans+=f(i);
			if(i*i!=n)ans+=f(n/i);
		}
	}return ans;
}

int main(){
	
	return 0;
}
