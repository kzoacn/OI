#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,m,k;
typedef long long LL;
vector<int>O[maxn];
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
struct BIT{
	LL d[maxn];
	inline int lowbit(int x){return x&-x;}
	LL get(int x){
		LL ans=0;
		while(x)ans+=d[x],x-=lowbit(x);
		return ans;
	}
	void updata(int x,LL f){
		while(x<=m)d[x]+=f,x+=lowbit(x);
	}
	void add(int l,int r,LL f){
		updata(l,f);
		updata(r+1,-f);
	}
}T,T2;
int anss[maxn],wana[maxn];
struct qes{
	LL x,y,z;
	qes(LL _x=0,LL _y=0,LL _z=0):
		x(_x),y(_y),z(_z){}
}q[maxn],p[maxn];
bool part(qes &q){
	if(q.y+q.z>=wana[q.x])return 1;
	q.z+=q.y;q.y=0;return 0;
}
void solve(int lef,int rig,int l,int r){
	if(l==r){
		for(int i=lef;i<=rig;i++)if(anss[p[i].x]!=-1)
		anss[p[i].x]=l;return;
	}int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++){
		if(q[i].x<=q[i].y)T.add(q[i].x,q[i].y,q[i].z);
		else T.add(1,q[i].y,q[i].z),T.add(q[i].x,m,q[i].z);
	}for(int i=lef;i<=rig;i++){
		p[i].y=0;
		for(int j=0;j<O[p[i].x].size()&&p[i].y<=int(1e9)+1;j++)
		p[i].y+=T.get(O[p[i].x][j]);
	}for(int i=l;i<=mid;i++){
		if(q[i].x<=q[i].y)T.add(q[i].x,q[i].y,-q[i].z);
		else T.add(1,q[i].y,-q[i].z),T.add(q[i].x,m,-q[i].z);
	}int dv=stable_partition(p+lef,p+rig+1,part)-p-1;		
	if(lef<=dv)
	solve(lef,dv,l,mid);
	if(dv+1<=rig)
	solve(dv+1,rig,mid+1,r);
}
int main(){
	n=getint();m=getint();
	for(int i=1;i<=m;i++){
		int x=getint();O[x].push_back(i);
	}for(int i=1;i<=n;i++)wana[i]=getint(),p[i]=qes(i,0,0);
	k=getint();
	for(int i=1;i<=k;i++){
		int l=getint(),r=getint(),x=getint();
		q[i]=qes(l,r,x);
	}q[++k]=qes(1,m,int(1e9)+1);
	solve(1,n,1,k);	
	for(int i=1;i<=n;i++)if(anss[i]!=k)
	printf("%d\n",anss[i]);else puts("NIE");
	return 0;
}
