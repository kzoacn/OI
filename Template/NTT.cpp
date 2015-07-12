#include<bits/stdc++.h>
using namespace std;
const int M=998244353;
const int mo=1e9+7;
const int G=3;
const int maxn=(1<<18)+5;
typedef long long LL;
LL pw(LL x,LL k,LL p){LL a=1;for(;k;k>>=1,x=x*x%p)if(k&1)a=a*x%p;return a;}
int n,m,N,flag,inv[maxn];
int a[maxn],b[maxn],tmp[maxn];
void NTT(int *a,int n){
	if(n==1)return;
	register int i;
	for(i=0;i<n;i++)
	if(i&1)tmp[i/2+n/2]=a[i];
	else tmp[i/2]=a[i];
	
	//copy(tmp,tmp+n,a);
	for(i=0;i<n;i++)a[i]=tmp[i];
	
	NTT(a,n>>1);
	NTT(a+n/2,n>>1);

	register int w=1,wn=pw(G,(M-1)/n,M),x,y;
	if(flag==-1)wn=pw(wn,M-2,M);	
	for(i=0;i<n/2;i++){
		x=a[i],y=a[i+n/2];
		a[i]=(x+(LL)y*w%M)%M;
		a[i+n/2]=(x-(LL)y*w%M+M)%M;
		w=(LL)w*wn%M;
	}
}
int main(){
	scanf("%d%d",&n,&m);n++;m++;
	N=1;while(N<max(n,m))N<<=1;N<<=1;
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int i=0;i<m;i++)scanf("%d",&b[i]);
	flag=1;
	NTT(a,N);
	NTT(b,N);
	for(int i=0;i<N;i++)a[i]=(LL)a[i]*b[i]%M;	
	flag=-1;
	NTT(a,N);
	LL invN=pw(N,M-2,M);
	for(int i=0;i<N;i++)a[i]=(LL)a[i]*invN%M;
	for(int i=0;i<n+m-1;i++)
		printf("%d%c",a[i]," \n"[i+1==n+m-1]);
	return 0;
}
