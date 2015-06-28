#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int q,n;
#define ls i<<1
#define rs i<<1|1
#define lson i<<1,l,(l+r)/2
#define rson i<<1|1,(l+r)/2+1,r
struct sgt{
	int laz[maxn*4];
	void build(int i,int l,int r){
		laz[i]=-1;
		if(l==r){
			laz[i]=0;
			return ;
		}
		build(lson);
		build(rson);
	}
	void pd(int i){
		if(laz[i]==-1)return;
		laz[ls]=max(laz[ls],laz[i]);
		laz[rs]=max(laz[rs],laz[i]);
		laz[i]=-1;
	}
	int Q(int i,int l,int r,int ps){
		if(l==r)return laz[i];
		pd(i);
		if(ps<=(l+r)/2)return Q(lson,ps);
		else return Q(rson,ps);
	}
	void C(int i,int l,int r,int l0,int r0,int x){
		if(l0<=l&&r0>=r)return void(laz[i]=x);
		if(l0<=(l+r)/2)C(lson,l0,r0,x);
		if(r0>(l+r)/2)C(rson,l0,r0,x);
	}
	int Q(int ps){return Q(1,1,n,ps);}
	void C(int l,int r,int x){C(1,1,n,l,r,x);}
}T[2];
vector<int>M1,M2;
int qx[maxn],qy[maxn],aim[maxn];
int main(){
	scanf("%*d%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&qx[i],&qy[i]);
		char ty=getchar();
		while(!isalpha(ty))ty=getchar();
		aim[i]=ty=='L'?1:2;
		M1.push_back(qx[i]);
		M2.push_back(qy[i]);
	}n=1;
	sort(M1.begin(),M1.end());
	sort(M2.begin(),M2.end());
	M1.erase(unique(M1.begin(),M1.end()),M1.end());
	M2.erase(unique(M2.begin(),M2.end()),M2.end());
	n=M1.size();
	T[0].build(1,1,n);	
	T[1].build(1,1,n);	
	for(int i=1;i<=q;i++){
		int ty=aim[i];
		if(ty==1){
			int x=lower_bound(M1.begin(),M1.end(),qx[i])-M1.begin()+1;
			int y=lower_bound(M2.begin(),M2.end(),qy[i])-M2.begin()+1;
			int lef=T[1].Q(y);
			printf("%d\n",qx[i]-lef);
			T[0].C(lef);
		}else{
			
		}
	}
	return 0;
}
