#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
const LL mo=7528443412579576937LL;
struct mat{
	LL a[2][2];
	void clear(){memset(a,0,sizeof a);}
	void unit(){for(int i=0;i<2;i++)a[i][i]=1;}
	LL* operator[](int x){return a[x];}
	LL at(int x,int y)const{return a[x][y];}
	void ass(){for(int i=0;i<2;i++)for(int j=0;j<2;j++)assert(a[i][j]>=0);}
};
LL mul(LL x,LL y){
	LL ans=0;
	x%=mo;y%=mo;
	for(;y;y>>=1){
		if(y&1)ans=(ans+x)%mo;
		x=(x+x)%mo;
	}return ans;
}
mat operator*(mat A,mat B){
	mat ans;ans.clear();
	for(int k=0;k<2;k++)
	for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
	ans[i][j]=(ans[i][j]+mul(A[i][k],B[k][j]))%mo;
	return ans;
}
mat pw(mat x,LL k,LL p=mo){
	mat ans;ans.clear();ans.unit();
	for(;k;k>>=1){
		if(k&1)ans=ans*x;
		x=x*x;
//		ans.ass();
//		x.ass();
	}return ans;
}
LL b,d,n;
mat A;
int main(){
	cin>>b>>d>>n;
	if(n==0){puts("1");return 0;}
	A[0][0]=b;A[0][1]=(d-b*b)/4;
	A[1][0]=1;A[1][1]=0;
	A=pw(A,n-1);
	LL ans=2*A[0][1]%mo+mul(b,A[0][0])-(d!=b*b&&n%2==0);
	cout<<ans%mo<<endl;
	return 0;
}
