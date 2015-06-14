#include<bits/stdc++.h>
#include<ext/hash_map>
using namespace std;
typedef long long LL;
const int maxn=2e6+6;
//const int maxn=5;
int p[maxn],notp[maxn];
LL phi[maxn],u[maxn];
void init(){
    u[1]=phi[1]=1;
    for(int i=2;i<maxn;i++){
        if(!notp[i]){
            p[++p[0]]=i;
            phi[i]=i-1;u[i]=-1;
        }
        for(int j=1;j<=p[0]&&p[j]*i<maxn;j++){
            notp[i*p[j]]=1;
            if(i%p[j]==0){
                phi[i*p[j]]=phi[i]*p[j];
                u[i*p[j]]=0;
                break;
            }else{
                phi[i*p[j]]=phi[i]*(p[j]-1);
                u[i*p[j]]=-u[i];
            }
        }
    }for(int i=2;i<maxn;i++)u[i]+=u[i-1],phi[i]+=phi[i-1];
}
typedef int ui;
__gnu_cxx::hash_map<ui,LL>_phi,_u;
LL Phi(int x){
	assert(x>0);
    if(x<maxn)return phi[x];
    if(_phi.count(x))return _phi[x];
    LL ans=x*(x+1LL)/2;
    if(x==2147483647)cerr<<ans<<endl;
    for(LL i=2,j;i<=x;i=j+1){
        j=x/(x/i);
        ans-=(LL)(j-i+1)*Phi(x/i);
    }if(ans<=0)cerr<<x<<endl;
	assert(ans>0);
	return _phi[x]=ans;
}
LL U(int x){
    if(x<maxn)return u[x];
    if(_u.count(x))return _u[x];
    LL ans=1;
    for(LL i=2,j;i<=x;i=j+1){
        j=x/(x/i);
        ans-=(LL)(j-i+1)*U(x/i);
    }return _u[x]=ans;  
}
int main(){
    init();
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        //printf("%lld %lld",Phi(n),U(n));
        //if(T)puts("");
        cout<<Phi(n)<<" "<<U(n)<<endl;
    }
    return 0;
}
