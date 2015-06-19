#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=111;
//const int BIT=51;
//LL mat[maxn][maxn][51];
int n,bit;
LL m;
struct mat{
	LL a[maxn][maxn];
	LL* operator[](int x){return a[x];}
	LL at(int x,int y)const{return a[x][y];}
	void clear(){memset(a,0,sizeof a);}
	LL mx(){
		LL mx=0;
		for(int i=1;i<=n;i++)mx=max(mx,a[1][i]);
		return mx;
	}
	bool empty()const{
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		if(a[i][j])return false;
		return true;
	}
}f[66],ma;
mat operator*(const mat &A,const mat &B){
	static mat C;C.clear();
	if(A.empty())return B;
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if((A.at(i,k)&&B.at(k,j)))
		C[i][j]=max(C[i][j],(A.at(i,k)+B.at(k,j)));
		if(C[i][j]>=m)C[i][j]=m;
	}return C;
}
void sol(){
	scanf("%d%lld",&n,&m);
	assert(m>1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		scanf("%lld",&f[0][i][j]);
		f[0][i][j]=min(f[0][i][j],m);
	}
	for(bit=1;bit<66;bit++){
		f[bit].clear();
		f[bit]=f[bit-1]*f[bit-1];
		if(f[bit].mx()>=m)break;
	}
	ma.clear();
	LL ans=0;
	for(LL b=bit;b>=0;b--){
		if((ma*f[b]).mx()<m){
			ma=ma*f[b];
			ans|=1LL<<b;
		}
	}printf("%lld\n",ans+1);	
}
int main(){
//	freopen("bzoj2165.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
