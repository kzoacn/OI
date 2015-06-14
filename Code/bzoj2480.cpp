#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pow(LL x,LL k,LL p){
    LL ans=1;
    for(;k;k>>=1){
        if(k&1)ans=ans*x%p;
        x=x*x%p;
    }return ans;
}
LL exgcd(LL a,LL b,LL &x,LL &y){
    if(!b){
        x=1;y=0;
        return a;
    }else{
        LL g=exgcd(b,a%b,x,y);
        LL t=x;x=y;y=t-a/b*y;
        return g;
    }
}
LL gcd(LL a,LL b){
    while(b){
        LL t=a%b;
        a=b;b=t;
    }return a;
}
LL lcm(LL a,LL b){return a*b/gcd(a,b);}
LL inv(LL a,LL p){
    LL x,y;
    LL d=exgcd(a,p,x,y);
    return d==1?(x+p)%p:-1;
}
void solve1(){
    int y,z,p;
    scanf("%d%d%d",&y,&z,&p);
    printf("%lld\n",pow(y,z,p));
}
LL BSGS(LL a,LL b,LL p){
    LL m=0;for(;m*m<=p;m++);
    map<LL,int>hash;hash[1]=0;
    LL e=1,amv=inv(pow(a,m,p),p);
    for(int i=1;i<m;i++){
        e=e*a%p;
        if(!hash.count(e))
            hash[e]=i;  
        else break;
    }
    for(int i=0;i<m;i++){
        if(hash.count(b))
            return hash[b]+i*m;
        b=b*amv%p;  
    }
    return -1;
}
bool solve2(){
    LL a,b,p;
    scanf("%lld%lld%lld",&a,&p,&b);
    if(!p)return false;
    b%=p;
    //if(b>=p)return (void)puts("Math Error");
    //a^x=b (mod p)
    LL e=1%p;
    for(int i=0;i<100;i++){
        if(e==b)return (void)printf("%d\n",i),1;
        e=e*a%p;
    }
    int r=0;
    while(gcd(a,p)!=1){
        LL d=gcd(a,p);
        if(b%d)return puts("No Solution"),1;
        p/=d;b/=d;b=b*inv(a/d,p);
        r++;
    }LL res=BSGS(a,b,p);
    if(res==-1)return puts("No Solution"),1;
    printf("%lld\n",res+r);
    return true;
}
int main(){
	while(solve2());
    return 0;
}
