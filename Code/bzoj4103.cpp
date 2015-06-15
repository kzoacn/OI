#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
const int BIT=32;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m,q;
int a[maxn],b[maxn];
struct node{
	int siz,sum;
	node *c[2];
	void rz(){
		sum=0;
		if(c[0])sum+=c[0]->sum;
		if(c[1])sum+=c[1]->sum;
	}
	node(){siz=0;c[0]=c[1]=0;sum=0;}
}*root[maxn],*x[maxn],*y[maxn];
#define siz(x) (x?x->siz:0)
#define sum(x) (x?x->sum:0)
#define c(x,d) (x?x->c[d]:0)
void insert(node *x,node *y,int val,int d){
	if(d<0){
		
		return;
	}
	int v=val>>d&1;
	x->c[v]=new node();
	if(c(y,v))*x->c[v]=*c(y,v);x->c[v]->sum++;
	x->c[!v]=c(y,!v);
	insert(c(x,v),c(y,v),val,d-1);
	x->rz();
}
int Q(int U,int D,int L,int R,int K){
	int ans=0,cur=0,tmp;
	for(int i=U;i<=D;i++)x[i]=root[R],y[i]=root[L-1];
	for(int i=BIT-1;i>=0;i--){
		tmp=0;
		for(int j=U;j<=D;j++)if(!(a[j]>>i&1))
			tmp+=(sum(x[j])-sum(c(x[j],1)))-(sum(y[j])-sum(c(y[j],1)));
		else tmp+=(sum(x[j])-sum(c(x[j],0)))-(sum(y[j])-sum(c(y[j],0)));
		
		if(tmp>=K){
			// 0
			for(int j=U;j<=D;j++){
				int v=a[j]>>i&1;
				x[j]=c(x[j],v);
				y[j]=c(y[j],v);
			}
		}else{
			K-=tmp;
			ans|=1<<i;
			for(int j=U;j<=D;j++){
				int v=!(a[j]>>i&1);
				x[j]=c(x[j],v);
				y[j]=c(y[j],v);
			}
		}
	}return ans;
}
int main(){
	freopen("bzoj4103.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=n;i++)a[i]=in();
	for(int i=1;i<=m;i++)b[i]=in();	
	for(int i=1;i<=m;i++){
		root[i]=new node();if(root[i-1])*root[i]=*root[i-1];
		insert(root[i],root[i-1],b[i],BIT-1);
	}
	q=in();
	while(q--){
		int u=in(),d=in(),l=in(),r=in(),k=(d-u+1)*(r-l+1)-in()+1;
		printf("%d\n",Q(u,d,l,r,k));
	}
	return 0;
}
