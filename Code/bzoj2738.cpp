#include<bits/stdc++.h>
using namespace std;
#define lw(x) (x&-x)
const int maxn=505;
int d[maxn][maxn];
int n,q;
void update(int x,int y,int delt){
	for(int i=x;i<=n;i+=lw(i))
	for(int j=y;j<=n;j+=lw(j))
		d[i][j]+=delt;
}
int get(int x,int y){
	int ans=0;
	for(int i=x;i;i-=lw(i))
	for(int j=y;j;j-=lw(j))
		ans+=d[i][j];
	return ans;
}
int get(int xl,int yl,int xr,int yr){
	int ans=0;
	ans+=get(xr,yr);
	ans-=get(xl-1,yr);
	ans-=get(xr,yl-1);
	ans+=get(xl-1,yl-1);
	return ans;
}
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int As;
struct add{
	int x,y,d;
	bool operator<(const add &o)const{return d<o.d;}
}A[maxn*maxn];
struct qes{
	int xl,yl,xr,yr,k,cur,id;
}Q[60001];
int anss[60001];
bool part(const qes &Q){
	return Q.cur>=Q.k;
}
void solve(int lef,int rig,int l,int r){
	if(l==r){
		for(int i=lef;i<=rig;i++)
			anss[Q[i].id]=A[l].d;
		return;
	}
	int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++)
		update(A[i].x,A[i].y,1);
	for(int i=lef;i<=rig;i++)
		Q[i].cur=get(Q[i].xl,Q[i].yl,Q[i].xr,Q[i].yr);
	int dv=partition(Q+lef,Q+rig+1,part)-Q-1;
	
	if(dv<rig)solve(dv+1,rig,mid+1,r);
	
	for(int i=l;i<=mid;i++)
		update(A[i].x,A[i].y,-1);
	
	if(lef<=dv)solve(lef,dv,l,mid);
		
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		int d=in();
		A[++As]=(add){i,j,d};
	}sort(A+1,A+1+As);
	for(int i=1;i<=q;i++){
//		scanf("%d%d%d%d%d",&Q[i].xl,&Q[i].yl,&Q[i].xr,&Q[i].yr,&Q[i].k);
		Q[i].xl=in();
		Q[i].yl=in();
		Q[i].xr=in();
		Q[i].yr=in();
		Q[i].k=in();
		Q[i].id=i;
	}

	solve(1,q,1,As);
	
	for(int i=1;i<=q;i++)
		printf("%d\n",anss[i]);
	return 0;
}
