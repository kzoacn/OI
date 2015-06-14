#include<bits/stdc++.h>
#include<ext/hash_map>
using namespace std;
typedef long long LL;
const int maxn=5e6+6;
//const int maxn=5;
int p[maxn],notp[maxn],Mx;
LL phi[maxn],u[maxn];
void init(int maxn){
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
__gnu_cxx::hash_map<int,LL>_phi,_u;
LL Phi(LL x){
	if(x<Mx)return phi[x];
	if(_phi.count(x))return _phi[x];
	LL ans=(LL)x*(x+1)/2;
	for(LL i=2,j;i<=x;i=j+1){
		j=x/(x/i);
		ans-=(LL)(j-i+1)*Phi(x/i);
	}return _phi[x]=ans;
}
LL U(LL x){
	if(x<Mx)return u[x];
	if(_u.count(x))return _u[x];
	LL ans=1;
	for(LL i=2,j;i<=x;i=j+1){
		j=x/(x/i);
		ans-=(LL)(j-i+1)*U(x/i);
	}return _u[x]=ans;	
}
int main(){
	int T;scanf("%d",&T);
	vector<int>vec;
	for(int i=1;i<=T;i++){
		int x;cin>>x;
		vec.push_back(x);
	}
	init(Mx=3*(int)pow(*max_element(vec.begin(),vec.end()),2.0/3.0));
	for(int i=0;i<T;i++){
		int n=vec[i];
		//printf("%lld %lld",Phi(n),U(n));
		//puts("");
		cout<<Phi(n)<<" "<<U(n)<<endl;
	}
	return 0;
}
