#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
typedef long long LL;
int n;
LL sumt[maxn],sumf[maxn],S,f[maxn];
int T[maxn],F[maxn];
int getint(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
struct point{
	LL x,y;
	point(LL x,LL y):x(x),y(y){}
	point operator-(point o){return point(x-o.x,y-o.y);}
	LL operator*(point o){return x*o.x+y*o.y;}
	LL operator^(point o){return x*o.y-y*o.x;}
	bool operator<(point o)const{return x!=o.x?x<o.x:y<o.y;}
};
struct CH{
	vector<point>ch;
	void push_back(point p){
		while(ch.size()>1&&(p-ch[ch.size()-1])*(ch[ch.size()-1]-ch[ch.size()-2])>=0)
			ch.pop_back();
		ch.push_back(p);
	}
	LL Qmin(point p){
		int l=0,r=ch.size()-1;
		LL ans=1LL<<62;
		while(r-l>3){
			int mid1=l+(r-l)/3;
			int mid2=r-(r-l)/3;
			if((ch[mid1]^p)<(ch[mid2]^p))
				r=mid2;
			else l=mid1;
		}for(int i=l;i<=r;i++)ans=min(ans,ch[i]^p);
		return ans;
	}
	void clear(){ch.clear();}
	int size()const{return ch.size();}
	point operator[](int x)const{return ch[x];}
};
vector<point>tmp;
CH C;
CH merge(const CH &L,const CH &R){
	C.clear();tmp.clear();
	for(int i=0;i<L.size();i++)tmp.push_back(L[i]);
	for(int i=0;i<R.size();i++)tmp.push_back(R[i]);
	sort(tmp.begin(),tmp.end());
	for(int i=0;i<tmp.size();i++)C.push_back(tmp[i]);
	return C;
}
CH solve(int l,int r){
	if(l==r){
		C.clear();
		C.push_back(point(f[l],-sumt[l]));
		return C;
	}int mid=(l+r)>>1;
	CH L,R;
	if(r>mid)R=solve(mid+1,r);
	for(int i=l;i<=mid;i++)
		f[i]=min(f[i],R.Qmin(point(1,sumf[i]))+S*sumf[i]+sumt[i]*sumf[i]);
	if(l<=mid)L=solve(l,mid);	
	return merge(L,R);
}
int main(){
	n=getint();S=getint();
	for(int i=1;i<=n;i++)T[i]=getint(),F[i]=getint();
	for(int i=n;i>=1;i--)sumt[i]=sumt[i+1]+T[i],sumf[i]=sumf[i+1]+F[i];
	for(int i=n;i>=1;i--){
		f[i]=1LL<<62;
		for(int j=i+1;j<=n+1;j++){
			f[i]=min(f[i],f[j]+(S+sumt[i]-sumt[j])*sumf[i]);
		}
	}
	
	cout<<f[1]<<endl;
	return 0;
}
