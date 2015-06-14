#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,n,p,q,phiq;
int notp[46341],prime[46341];
void get_p(){
	for(int i=2;i<46341;i++){
		if(!notp[i]){prime[++prime[0]]=i;}
		for(int j=1;j<=prime[0]&&i*prime[j]<46341;j++){
			notp[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int phi(int x){
	int ans=1;
	for(int j=1;j<=prime[0]&&prime[j]*prime[j]<=x;j++){
		int i=prime[j];
		if(x%i==0)ans=ans*(x-1),x/=i;
		while(x%i==0)ans=ans*x,x/=i;
	}if(x>1)ans=ans*(x-1);
	return ans;
}
struct matrix{
	int a[2][2];
	void clear(){memset(a,0,sizeof a);}
	void unit(){a[0][0]=a[1][1]=1;}
	int *operator[](int x){return a[x];}
	int at(int x,int y)const{return a[x][y];}
};
matrix operator*(const matrix &A,const matrix &B){
	matrix C;C.clear();
	for(int k=0;k<2;k++)
	for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
	C[i][j]=(C[i][j]+(LL)A.at(i,k)*B.at(k,j)%phiq)%phiq;
	return C;
}
matrix pw(matrix x,int k,LL p){
	matrix C;C.clear();C.unit();
	for(;k;k>>=1){
		if(k&1)C=C*x;
		x=x*x;
	}return C;
}
int pw(LL x,int k,int p){
	LL C=1;
	for(;k;k>>=1){
		if(k&1)C=C*x%p;
		x=x*x%p;
	}return C;
}
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int main(){
	get_p();
	scanf("%d%d",&T,&p);
	while(T--){
		n=getint();q=getint();
		if(n<=2){printf("%d\n",p%q);continue;}
		phiq=phi(q);
		matrix A;A.clear();
		A[0][0]=1;A[0][1]=1;
		A[1][0]=1;A[1][1]=0;
		A=pw(A,n-2,phiq);
		printf("%d\n",pw(p,(A[0][0]+A[0][1])%phiq+phiq,q));
	}
	return 0;
}
