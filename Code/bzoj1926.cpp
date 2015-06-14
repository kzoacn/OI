#include<bits/stdc++.h>
using namespace std;
#define mp(x) (lower_bound(w+1,w+1+w[0],x)-w)
typedef long long LL;
int R,C,m;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
struct node{
	int size;
	LL sum;
	node* c[2];
	void rz(){
		sum=(c[0]?c[0]->sum:0)+(c[1]?c[1]->sum:0);
	}
	node();
}*null=new node();
node::node(){size=sum=0;c[0]=c[1]=null;}
int w[int(500000)+1];
namespace solve1{
	node *root[int(500000)+1];
	int a[int(500000)+1];
	void insert(int l,int r,node *x,node *y,int val){
		if(x==null)x=new node();
		*x=*y;x->size++;
		if(l==r){x->sum=w[val];return;}
		int mid=(l+r)>>1;
		if(val<=mid){
			insert(l,mid,x->c[0],y->c[0],val);
		}else{
			insert(mid+1,r,x->c[1],y->c[1],val);
		}x->rz();
	}
	int Q(int l,int r,node *x,node *y,LL H){
		if(l==r)return 0;
		int mid=(l+r)>>1;
		if(x->c[1]->sum-y->c[1]->sum<=H){
			return Q(l,mid,x->c[0],y->c[0],H-(x->c[0]->sum-y->c[0]->sum))+(x->c[0]->size-y->c[0]->size);	
		}else{
			return Q(mid+1,r,x->c[1],y->c[1],H);
		}
	}
	void solve(){
		root[0]=null;
		for(int i=1;i<=C;i++)a[i]=getint(),w[++w[0]]=a[i];
		sort(w+1,w+1+C);w[0]=unique(w+1,w+1+w[0])-w-1;
		for(int i=1;i<=C;i++)insert(1,w[0],root[i]=null,root[i-1],mp(a[i]));
		while(m--){
			getint();int l=getint();
			getint();int r=getint();
			LL H=getint();
			if(root[r]->sum-(l!=1?root[l-1]->sum:0)<H)puts("Poor QLW");
			else printf("%d\n",Q(1,w[0],root[r],root[l-1],H));
		}
	}
}
namespace solve2{
	node *root[201][201];
	int a[201][201];
	void insert(int l,int r,node *x,node *y1,node *y2,node *y3,int val){
	
	}
	void solve(){
		for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
		a[i][j]=getint(),w[++w[0]]=a[i][j];
		sort(w+1,w+1+w[0]);w[0]=unique(w+1,w+1+w[0])-w-1;
		for(int i=1;i<=R;i++)root[i][0]=null;
		for(int i=1;i<=C;i++)root[0][i]=null;
		for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
		insert(1,w[0],root[i][j],root[i-1][j],root[i][j-1],root[i-1][j-1],mp(a[i][j]));
		
	}
}
int main(){
	null->c[0]=null->c[1]=null;
	scanf("%d%d%d",&R,&C,&m);
	if(R==1)solve1::solve();
	else solve2::solve();
	return 0;
}
