#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL p,k,a,g;
vector<LL>vec;
LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;
		return a;	
	}
	LL d=exgcd(b,a%b,x,y);
	LL t=x;x=y;y=t-a/b*y;
	return d;
}
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
LL BSGS(LL a,LL b,LL p){
	LL m=1;
	for(;m*m<p;m++);
	map<LL,int>hash;
	LL v=pw(pw(a,m,p),p-2,p);
	hash[1]=0;LL _a=a;
	for(int i=1;i<m;i++){
		hash[a]=i;
		a=a*_a%p;
	}
	for(int i=0;i<=m;i++){
		if(hash.count(b))	
			return hash[b]+i*m;
		b=b*v%p;
	}return -1;
}
bool check(int x){
	for(int i=0;i<vec.size();i++)	
		if(pw(x,(p-1)/vec[i],p)==1)
			return 0;
	return 1;
}
LL getroot(){
	LL tmp=p-1;
	for(int i=2;i*i<=tmp;i++){
		if(tmp%i==0){
			vec.push_back(i);
			while(tmp%i==0)tmp/=i;
		}
	}if(tmp>1)vec.push_back(tmp);
	for(int i=2;i<p;i++)
		if(check(i))return i;
	return -1;
}
vector<LL>anss;
void solve(LL a,LL b,LL c){
	LL x,y;
	LL d=exgcd(a,b,x,y);
	a/=d;b/=d;
	if(c%d){
		puts("0");
		return;
	}c/=d;
	x%=(b*d);
	x=(x+b*d)%(b*d);
	x*=c;
	while(x<p-1){
		anss.push_back(x);
		x+=b;y-=a;
	}
	for(int i=0;i<anss.size();i++)
		anss[i]=pw(g,anss[i],p);
	printf("%d\n",anss.size());
	sort(anss.begin(),anss.end());
	for(int i=0;i<anss.size();i++)
	printf("%lld\n",anss[i]);
}
int main(){
	cin>>p>>k>>a;
	if(a==0){
		puts("1");
		puts("0");
		return 0;
	}
	g=getroot();
	LL t=BSGS(g,a,p);
	solve(k,p-1,t);
	return 0;
}
