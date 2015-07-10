#include<bits/stdc++.h>
#include<pb_ds/priority_queue.hpp>
using namespace std;
const int maxn=250010;
__gnu_cxx::priority_queue<int>pr;
typedef long long LL;
struct P{
	int x,y,m,p;
	LL r;
}a[maxn],s;
LL X[maxn];
int n;
struct byM{
	inline bool operator()(const int &x,const int &y){return a[x].m!=a[y].m?a[x].m>a[y].m:x>y;}
};
bool vis[maxn];
priority_queue<int,vector<int>,byM>d[maxn];
inline void insert(int x,const int &id){
	while(x<=X[0]){
		d[x].push(id);
		x+=x&-x;
	}
}
P q[maxn];
int head;
int ans=0;
inline void get(int x,int y){
	if(x<=0)return ;
	while(x){
		while(!d[x].empty()){
			int id=d[x].top();
			if(a[id].m>y)break;
			d[x].pop();			
			if(vis[id])continue;vis[id]=1;
			q[head++]=a[id];
			ans++;
		}
		x-=x&-x;
	}
}
inline LL sqr(const LL &x){return x*x;}
inline LL dis(const P &a,const P &b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
inline int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:1,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int main(){
	freopen("bzoj3276.in","r",stdin);
	scanf("%d%d%d%lld%d",&s.x,&s.y,&s.p,&s.r,&n);s.r=s.r*s.r;
	for(int i=1;i<=n;i++)
		a[i].x=in(),a[i].y=in(),a[i].m=in(),a[i].p=in(),a[i].r=in(),
		X[++X[0]]=dis(a[i],s),a[i].r=a[i].r*a[i].r;
	sort(X+1,X+1+X[0]);
	X[0]=unique(X+1,X+1+X[0])-X-1;
	for(int i=1;i<=n;i++)
		insert(lower_bound(X+1,X+1+X[0],dis(a[i],s))-X,i);
	q[head++]=s;
	while(head){
		P s=q[--head];
		get(upper_bound(X+1,X+1+X[0],s.r)-X-1,s.p);
	}cout<<ans<<endl;
	return 0;
}
