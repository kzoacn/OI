#include<bits/stdc++.h>
#define fst first
#define sec second
using namespace std;
typedef long long LL;
vector<int>fac;
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
LL pk;
bool check(int x){
	for(int i=0;i<fac.size();i++){
		if(pow(x,(pk-1)/fac[i],pk)==1)
			return 0;
	}return 1;
}
int getrt(LL p,LL k){
	fac.clear();
	pk=pow(p,k,1e18)-1;
	for(int i=2;i*i<=pk;i++){
		if(pk%i==0)fac.push_back(i);	
		while(pk%i==0)pk/=i;		
	}if(pk!=1)fac.push_back(pk);	
	pk=pow(p,k,1e18);
	for(int i=2;i<23333333;i++)
	if(check(i))return i;
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
LL solve(LL A,LL B,LL p,LL k){
	LL P=pow(p,k,1e18);B%=P;
	if(B==0)return pow(p,k-((k+A-1)/A),1e18);
	LL d=__gcd(B,P),s=1;
	for(int i=0;i<60;i++){
		if(d==s){s=i;break;}
		s=s*p;
	}if(s%A)return 0;
	LL g=getrt(p,1);
	B/=d;k-=s;
	LL phiP=(p-1)*pow(p,k-1,1e18);
	B=BSGS(g,B,P);
	if(B%__gcd(A,phiP))return 0;	
	return __gcd(A,phiP)*pow(p,s-s/A,1e18);
}
void solve(){
	LL A,B,P;scanf("%lld%lld%lld",&A,&B,&P);P=P*2+1;
	vector<pair<int,int> >vec;
	for(int i=2;i*i<=P;i++){
		if(P%i==0){
			P/=i;
			vec.push_back(make_pair(i,1));
			while(P%i==0)vec.back().sec++,P/=i;
		}
	}if(P!=1)vec.push_back(make_pair(P,1));
	LL ans=1;
	for(int i=0;i<vec.size();i++)
		ans=ans*solve(A,B,vec[i].fst,vec[i].sec);
	 printf("%lld\n",ans);
}
int main(){
	freopen("bzoj2219.in","r",stdin);
	int T;scanf("%d",&T);	
	while(T--)
		solve();
	return 0;
}
