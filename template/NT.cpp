#include<cstdio>
#include<map>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<cmath>
#include<cctype>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int n=1000;
bool p[maxn];
int prime[maxn];
int phi[maxn];
int mu[maxn];
LL fac[maxn];
LL _inv[maxn];
LL fat[maxn];
void get_p(){
	phi[1]=mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!p[i]){
			prime[++prime[0]]=i;
			phi[i]=i-1;mu[i]=-1;
		}for(int j=1;j<=prime[0];j++){
			if(i*prime[j]>n)break;
			p[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}else{
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
}
void get_fac(LL p){
	fac[0]=1;
	for(int i=1;i<=p;i++)fac[i]=fac[i-1]*i%p;
}
void get_inv(LL p){
	_inv[1]=1;
	for(int i=2;i<=p;i++)_inv[i]=(p-p/i)*_inv[p%i]%p;
}
LL gcd(LL a,LL b){
	while(b){
		LL t=a%b;
		a=b;
		b=t;
	}return a;
}
LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;return a;
	}else{
		LL d=exgcd(b,a%b,x,y);
		LL t=x;x=y;y=t-a/b*y;
		return d;
	}
}
LL _phi(LL x){
	LL ans=x;
	for(int i=2;i*i<=x;i++){
	if(x%i==0){
			ans=ans*i/(i-1);
			while(x%i==0)x/=i;
		}
	}if(x>1)ans=ans/x*(x-1);
	return ans;
}
LL _mul(LL x,LL y,LL p){
	LL ans=0;
	for(;y;y>>=1){
		if(y&1)ans=(ans+x)%p;
		x=(x+x)%p;
	}return ans;
}
LL mul(LL x,LL y,LL p){  
    if(y==0)return 0;  
    if(y==1)return x%p;  
    LL res=mul(x,y>>1,p);  
    if((y&1)==1)return (res+res+x)%p;  
    else return (res+res)%p;  
}  
LL power(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=mul(ans,x,p);
		x=mul(x,x,p);
	}return ans;
}
LL inv(LL a,LL p){
	LL d,x,y;
	d=exgcd(a,p,x,y);
	return d==1?(x+p)%p:-1;
}
LL china(int n,int *a,int *m){
	LL M=1,d,x=0,y;
	for(int i=0;i<n;i++)M*=m[i];
	for(int i=0;i<n;i++){
		LL w=M/m[i];
		d=exgcd(m[i],w,d,y);
		x=(x+y*w*a[i])%M;
	}while(x<=0)x+=M;return x;
}
LL BSGS(LL a,LL b,LL p){
	LL m=sqrt(p)+.5,v=inv(power(a,m,p),p),e=1;
	map<LL,LL>hash;hash[1]=0;
	for(int i=1;i<m;i++)
		e=e*a%p,hash[e]=i;
	for(int i=0;i<=m;i++){
		if(hash.count(b))return i*m+hash[b];
		b=b*v%p;
	}return -1;
}
LL C(LL n,LL m,LL p){
	if(n<m)return 0;
	return fac[n]*inv(fac[m]*fac[n-m]%p,p)%p;
}
LL _C(LL n,LL m,LL p){
	if(n<m)return 0;
	LL ans=1,res=1;
	for(int i=1;i<=n;i++)ans=ans*i%p;
	for(int i=1;i<=n-m;i++)res=res*i%p;
	for(int i=1;i<=m;i++)res=res*i%p;
	res=inv(res,p);
	ans=(ans*res)%p;
}
LL Lucas(LL n,LL m,LL p){
	LL ans=1;
	while(n&&m){
		LL a=n%p,b=m%p;
		if(a<b)return 0;
		ans=(ans*C(a,b,p))%p;
		n/=p;m/=p;
	}return ans;
}
bool isprime(LL x){
	LL sqrtx=sqrt(x);
	if(x==1)return false;	
	for(int i=1;i<=7;i++){
		LL a=rand()%(x-1)+1;
		if(power(a,x-1,x)!=1)return false;					
	}return true;
}
LL prho(LL n,LL c){
	LL i=1,k=2,x=rand()%(n-1)+1,y=x;
	while(1){
		i++;x=(x*x%n+c)%n;
		LL d=gcd((y-x+n)%n,n);
		if(d>1&&d<n)return d;
		if(y==x)return n;
		if(i==k)y=x,k<<=1;
	}
}
void factor(LL n,LL c){
	if(n==1)return;
	if(isprime(n)){
		fat[++fat[0]]=n;
		return;
	}LL p=n,k=c;
	while(p>=n)p=prho(p,c--);
	factor(p,k);
	factor(n/p,k);
}
int main(){  

	return 0;  
}  
