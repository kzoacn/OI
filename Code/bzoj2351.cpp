#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
const int maxn=1001;
uint hashp[maxn],hashq[maxn],hash[maxn][maxn],p=97,q=233;
int n,m,A,B;
char s[maxn];
uint val[maxn*maxn];
int size,a[maxn][maxn];
uint get(int x1,int y1,int x2,int y2){
	uint ans=hash[x2][y2];
	ans-=hash[x2][y1-1]*hashq[y2-y1+1];
	ans-=hash[x1-1][y2]*hashp[x2-x1+1];
	ans+=hash[x1-1][y1-1]*hashq[y2-y1+1]*hashp[x2-x1+1];
	return ans;
}
//uint _hash[maxn][maxn];
int main(){
	scanf("%d%d%d%d",&n,&m,&A,&B);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
		a[i][j]=s[j]=='1';
	}
	hashp[0]=hashq[0]=1;
	for(int i=1;i<=m;i++)hashq[i]=hashq[i-1]*q;
	for(int i=1;i<=n;i++)hashp[i]=hashp[i-1]*p;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	hash[i][j]=q*hash[i][j-1]+p*hash[i-1][j]-hash[i-1][j-1]*p*q+a[i][j];
	for(int i=1;i+A-1<=n;i++)
	for(int j=1;j+B-1<=m;j++)
	val[size++]=get(i,j,i+A-1,j+B-1);
	sort(val,val+size);
	int Q;scanf("%d",&Q);
	while(Q--){
		uint v=0;
		for(int i=1;i<=A;i++){
			scanf("%s",s+1);
			v=v*p;uint vv=0;
			for(int j=1;j<=B;j++)
			vv=vv*q+s[j]-'0';
			v+=vv;
			//_hash[i][j]=q*_hash[i][j-1]+p*_hash[i-1][j]-_hash[i-1][j-1]*p*q+s[j]-'0';
		}
		if(binary_search(val,val+size,v))puts("1");else puts("0");
	}
	return 0;
}
