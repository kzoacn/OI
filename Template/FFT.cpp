#include<bits/stdc++.h>
using namespace std;
typedef complex<double> cp;
const int maxn=1<<18;
const double pi=acos(-1);
cp a[maxn],b[maxn],tmp[maxn];
int n,N;
void FFT(cp *a,int n,int f){
    if(n==1)return ;
    copy(a,a+n,tmp);
    for(int i=0;i<n;i++)if(i&1)a[(i>>1)+n/2]=tmp[i];else a[i>>1]=tmp[i];
     
    FFT(a,n/2,f);
    FFT(a+n/2,n/2,f);
    cp w(1,0),wn(cos(2*pi/n),f*sin(2*pi/n));
    for(int i=0;i<n/2;i++){
        cp x=a[i],y=a[i+n/2];
        a[i]=x+y*w;
        a[i+n/2]=x-y*w;
        w=w*wn;
    }
}
int main(){
//  freopen("bzoj2194.in","r",stdin);
    scanf("%d",&n);N=1;
    while(N<n)N<<=1;N<<=1;
    for(int i=0;i<n;i++){
        double x,y;scanf("%lf%lf",&x,&y);
        a[n-i-1]=x;
        b[i]=y;
    }
    FFT(a,N,1);
    FFT(b,N,1);
    for(int i=0;i<N;i++)a[i]*=b[i];
    FFT(a,N,-1);
    for(int i=0;i<N;i++)a[i]/=N;
    for(int i=n-1;i>=0;i--)
        printf("%d\n",int(a[i].real()+.5));
    return 0;
}
