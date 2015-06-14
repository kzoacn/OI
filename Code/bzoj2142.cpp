#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,m,w[6],P;
vector<pair<LL,LL> >vec;
vector<vector<LL> >fac;
vector<vector<LL> >cnt;
LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;return a;
	}else{
		LL d=exgcd(b,a%b,x,y);
		LL t=x;x=y;y=t-a/b*y;
		return d;
	}
}
LL inv(LL a,LL p){
	LL x,y;
	LL d=exgcd(a,p,x,y);
	return d==1?(x+p)%p:-1;
}
LL china(int n,LL a[],LL m[]){
	LL M=accumulate(m+1,m+1+n,1,multiplies<LL>());
	LL x=0;
	for(int i=1;i<=n;i++){
		LL w=M/m[i];
		LL wv=w*inv(w,m[i])%M;
		x=(x+wv*a[i]%M)%M;
	}return (x+M)%M;
}
LL pw(LL x,LL k){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x;
		x=x*x;
	}return ans;
}LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
LL C(LL n,LL m,pair<LL,LL> p){
	if(n<m)return 0;
	/*static LL fac[int(1e5+5)],cnt[int(1e5+5)];
	fac[0]=1;LL pp=pw(p.first,p.second);
	for(LL i=1;i<=n;i++){
		LL x=i;cnt[i]=cnt[i-1];
		while(x%p.first==0)cnt[i]++,x/=p.first;
		fac[i]=fac[i-1]*x%pp;
	}*/
	LL ans=fac[n];
	ans=ans*inv(fac[m],pp)%pp;
	ans=ans*inv(fac[n-m],pp)%pp;
	ans=ans*pw(p.first,cnt[n]-cnt[m]-cnt[n-m])%pp;
	return ans;
}
LL Lucas(LL n,LL m,pair<LL,LL> p){
	
}
LL C(LL n,LL m){
	LL a[65],_m[65],_n=0;
	for(int i=0;i<vec.size();i++){
		_n++;
		_m[_n]=pw(vec[i].first,vec[i].second);
		a[_n]=Lucas(n,m,vec[i]);		
	}return china(_n,a,_m);
}
int main(){
	cin>>P>>n>>m;LL sum=0;
	for(int i=1;i<=m;i++)cin>>w[i],sum+=w[i];
	if(sum>n){puts("Impossible");return 0;}
	LL p=P;
	for(LL i=2;i*i<=P;i++){
		while(p%i==0){
			if(vec.empty()||vec.back().first!=i)
				vec.push_back(make_pair(i,1));
			else vec.back().second++; 
			p/=i;
		}
	}if(p!=1)vec.push_back(make_pair(p,1));
	fac.resize(vec.size());
	for(int i=0;i<vec.size();i++){
		LL pp=pw(vec[i].first,vec[i].second);
		fac[i].resize(pp);
		fac[i][0]=1;
		for(int j=1;j<pp;j++){
			int x=j;cnt[i][j]=cnt[i][j-1];
			while(x%pp==0)cnt[i][j]++,x/=pp;
			fac[i][j]=fac[i][j-1]*x%pp;
		}
	}
	
	LL ans=C(n,sum);
	for(int i=1;i<=m;i++){
		ans=ans*C(sum,w[i])%P;
		sum-=w[i];
	}cout<<ans<<endl;
	return 0;
}
