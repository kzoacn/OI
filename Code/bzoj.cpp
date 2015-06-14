#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
typedef long long LL;
int getint(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
int n;
int a[maxn];
LL sum[maxn],ans;
struct point{
	LL x,y;
	point(LL x=0,LL y=0):x(x),y(y){}
	LL operator*(point o){return x*o.y-y*o.x;}
	LL operator^(point o){return x*o.x+y*o.y;}
	point operator-(point o){return point(x-o.x,y-o.y);}
	bool operator<(point o){return x!=o.x?x<o.x:y<o.y;}
};
struct CH{
	vector<point>ch;
	void push_back(point p){
//		cerr<<p.x<<" "<<p.y<<endl;
		while(ch.size()>1&&(p-ch.back())*(ch.back()-ch[ch.size()-2])<=0)ch.pop_back();
		ch.push_back(p);
	}
	LL Qmax(point p){
		LL ans=-(1LL<<62);
		int l=0,r=ch.size()-1;
		while(r-l>3){
			int mid1=l+(r-l)/3;
			int mid2=r-(r-l)/3;
			if((ch[mid1]^p)>(ch[mid2]^p))
				r=mid2;
			else l=mid1;
		}for(int i=l;i<=r;i++)ans=max(ans,ch[i]^p);
		return ans;
	}
	void clear(){ch.clear();}
}C;
int main(){
	n=getint();
	for(int i=1;i<=n;i++)a[i]=getint();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	LL ans1=-(1LL<<62),ans2=-(1LL<<62);
	for(int i=1;i<=n;i++){
		C.push_back(point(i,sum[i-1]));
		LL res=C.Qmax(point(-a[i],1))+(i+1)*a[i]+(sum[n]-sum[i]);
		ans=max(ans,res);
	}cout<<ans1<<endl<<ans2<<endl;
	return 0;
}
