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
void solve2(){
    LL a,b,p;
    scanf("%lld%lld%lld",&a,&b,&p);
    b%=p;
    //if(b>=p)return (void)puts("Math Error");
    //a^x=b (mod p)
    LL e=1%p;
    for(int i=0;i<100;i++){
        if(e==b)return (void)printf("%d\n",i);
        e=e*a%p;
    }
    int r=0;
    while(gcd(a,p)!=1){
        LL d=gcd(a,p);
        if(b%d)return (void)puts("Math Error");
        p/=d;b/=d;b=b*inv(a/d,p);
        r++;
    }LL res=BSGS(a,b,p);
    if(res==-1)return (void)puts("Math Error");
    printf("%lld\n",res+r);
}
void sol(LL a,LL b,LL c,LL &x,LL &y){
    LL d=exgcd(a,b,x,y);
    x=x*c/d;y=y*c/d;
}
void merge(LL &A,LL &B,LL a,LL b){
    LL x,y;
    sol(A,-a,b-B,x,y);
    A=lcm(A,a); 
    B=(a*y+b)%A;
    B=(B+A)%A;
}
LL prod=1,P;
pair<LL,LL> comput(LL n,LL p,LL k){
    if(n<=1)return make_pair(0,1);
    LL ans=1,cnt=0;
    ans=pow(prod,n/P,P);
    cnt=n/p;
    pair<LL,LL>res=comput(n/p,p,k);
    cnt+=res.first;
    ans=ans*res.second%P;
    for(int i=n-n%P+1;i<=n;i++)if(i%p){
     
        ans=ans*i%P;
    }
    return make_pair(cnt,ans);
}
pair<LL,LL> calc(LL n,LL p,LL k){
    prod=1;P=pow(p,k,1e18);
    for(int i=1;i<P;i++)if(i%p)prod=prod*i%P;
    pair<LL,LL> res=comput(n,p,k);
//  res.second=res.second*pow(p,res.first%k,P)%P;
//  res.first-=res.first%k; 
    return res;
}
LL calc(LL n,LL m,LL p,LL k){
    pair<LL,LL>A,B,C;
    LL P=pow(p,k,1e18);
    A=calc(n,p,k);
    B=calc(m,p,k);
    C=calc(n-m,p,k);
    LL ans=1;
    ans=pow(p,A.first-B.first-C.first,P);
    ans=ans*A.second%P*inv(B.second,P)%P*inv(C.second,P)%P;
    return ans;
}
void solve3(){
    LL n,m,P;scanf("%lld%lld%lld",&m,&n,&P);
    if(n<m)return (void)puts("0");
    //C(n,m) mod P
    //P=\prod p_i^{a_i} 
    //n! = p^x \times s
    //CRT ?
    vector<pair<int,int> >vec;
    for(int i=2;i<=P;i++){
        if(P%i==0){
            vec.push_back(make_pair(i,1));
            P/=i;
            while(P%i==0){
                vec.back().second++;
                P/=i;
            }
        }
    }
    LL A=1,B=0;
    for(int i=0;i<vec.size();i++)
        merge(A,B,pow(vec[i].first,vec[i].second),calc(n,m,vec[i].first,vec[i].second));    
    printf("%lld\n",B);
}
int main(){
    int T;scanf("%d",&T);   
    while(T--){
        int ty;scanf("%d",&ty);
        if(ty==1)solve1();
        else if(ty==2)solve2();
        else solve3();
    }
    return 0;
}
