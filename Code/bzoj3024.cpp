#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
typedef long long LL;
typedef long long LD;
LL getLL(){
	LL res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
int n;
LL a[maxn];
LL sum[maxn],ans;
struct poLL{
	LL x,y;
	poLL(LL x=0,LL y=0):x(x),y(y){}
	LD operator*(poLL o){return (LD)x*o.y-y*o.x;}
	LD operator^(poLL o){return (LD)x*o.x+y*o.y;}
	poLL operator-(poLL o){return poLL(x-o.x,y-o.y);}
	bool operator<(poLL o){return x!=o.x?x<o.x:y<o.y;}
};
struct CH{
	vector<poLL>ch;
	void push_back(poLL p){
//		cerr<<p.x<<" "<<p.y<<endl;
		while(ch.size()>1&&(p-ch.back())*(ch.back()-ch[ch.size()-2])<=0)ch.pop_back();
		ch.push_back(p);
	}
	LL Qmax(poLL p){
		LL ans=-(1LL<<62);
		int l=0,r=ch.size()-1;
		while(r-l>3){
			LL mid1=l+(r-l)/3;
			LL mid2=r-(r-l)/3;
			if((ch[mid1]^p)>=(ch[mid2]^p))
				r=mid2;
			else l=mid1;
		}for(LL i=l;i<=r;i++)ans=max(ans,(LL)(ch[i]^p));
		return ans;
	}
	void clear(){ch.clear();}
}C;
int main(){
	n=getLL();
	for(LL i=1;i<=n;i++)a[i]=getLL();
	for(LL i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	ans=-(1LL<<62);
	deque<int>dq;
	for(LL i=1;i<=n;i++){
		LL res=C.Qmax(poLL(-a[i],1))+(i+1)*a[i]+(sum[n]-sum[i]);
		ans=max(ans,res);
		C.push_back(poLL(i,sum[i-1]));
	}cout<<ans<<endl;
	reverse(a+1,a+1+n);
	for(LL i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	ans=-(1LL<<62);C.clear();
	for(LL i=1;i<=n;i++){
		LL res=C.Qmax(poLL(-a[i],1))+(i+1)*a[i]+(sum[n]-sum[i]);
		ans=max(ans,res);
		C.push_back(poLL(i,sum[i-1]));
	}cout<<ans;
	return 0;
}
