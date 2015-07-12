#include<bits/stdc++.h>
using namespace std;
typedef complex<double> cp;
const int maxn=1<<18;
const double pi=acos(-1);
cp a[maxn],b[maxn],tmp[maxn];
int n,N;
void FFT(cp *a,int n,int f){
	if(n==1)return;
	for(int i=0;i<n;i++)
	if(i&1)tmp[i/2+n/2]=a[i];
	else tmp[i/2]=a[i];
	copy(tmp,tmp+n,a);
	FFT(a,n>>1,f);
	FFT(a+n/2,n>>1,f);
	cp w(1,0),wn(cos(2*pi/n),f*sin(2*pi/n));
	for(int i=0;i<n/2;i++){
		cp x=a[i],y=a[i+n/2];
		a[i]=x+y*w;
		a[i+n/2]=x-y*w;
		w=w*wn;
	}
}
int m;
int main(){
//  freopen("bzoj2194.in","r",stdin);
    scanf("%d",&n);
	scanf("%d",&m);
	n++;m++;
	N=1;
    while(N<max(n,m))N<<=1;N<<=1;
    for(int i=0;i<n;i++)scanf("%lf",&a[i].real());
    for(int i=0;i<m;i++)scanf("%lf",&b[i].real());
    
    FFT(a,N,1);
    FFT(b,N,1);
    for(int i=0;i<N;i++)a[i]*=b[i];
    FFT(a,N,-1);
    for(int i=0;i<N;i++)a[i]/=N;
    for(int i=0;i<n+m-1;i++)
        printf("%d%c",int(a[i].real()+.5)," \n"[i+2==n+m]);
    return 0;
}
