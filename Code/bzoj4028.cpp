#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
const int sqrtmaxn=400;
int n,m,sqrtn;
template<class T>
T getn(){
	T res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
map<int,int>M[sqrtmaxn];
int Gcd[maxn];
int Xor[maxn],a[maxn];
int lef[sqrtmaxn],rig[sqrtmaxn];
void rebuild(int l,int r){
	if(l>=n)return;
	int id=l/sqrtn;
	Gcd[l]=Xor[l]=a[l];
	M[id].clear();
	for(int i=l+1;i<=r;i++)
		Gcd[i]=__gcd(Gcd[i-1],a[i]);
	for(int i=l+1;i<=r;i++)
		Xor[i]=Xor[i-1]^a[i];
	for(int i=r;i>=l;i--)
		M[id][Xor[i]]=i;
}
int Q(int l,int r,LL x,int cur,LL xcur){
	for(int i=l;i<=r;i++){
		cur=__gcd(cur,a[i]);
		if((LL)cur*(xcur^Xor[i])==x)
			return i;
	}return n;
}
void Q(LL x){
	int cur=0;
	LL xcur=0;
	for(int i=0;i<sqrtn;i++){
		if(lef[i]==n)break;
		if(cur==__gcd(cur,Gcd[rig[i]])){
			if(M[i].count((x/cur)^xcur))
				return (void)printf("%d\n",M[i][(x/cur)^xcur]);
		}else{
			int res=Q(lef[i],rig[i],x,cur,xcur);
			if(res!=n)return (void)printf("%d\n",res);
		}cur=__gcd(cur,Gcd[rig[i]]);
		xcur^=Xor[rig[i]];
	}puts("no");
}
int main(){
	n=getn<int>();sqrtn=ceil(sqrt(n));
	for(int i=0;i<n;i++)a[i]=getn<int>();
	for(int i=0;i<sqrtn;i++){
		lef[i]=i?rig[i-1]+1:0;
		rig[i]=min(lef[i]+sqrtn-1,n-1);
		rebuild(lef[i],rig[i]);
	}
	m=getn<int>();
	while(m--){
		char op[9];scanf("%s",op);
		if(op[0]=='M'){
			int x=getn<int>(),y=getn<int>();
			a[x]=y;rebuild(lef[x/sqrtn],rig[x/sqrtn]);
		}else Q(getn<LL>());
	}
	return 0;
}
