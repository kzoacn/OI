#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
const int BIT=3;
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
#define sum(x) (x?((!x->c[0]&&!x->c[1])?1:x->sum):0)
#define c(x,d) (x?x->c[d]:0)
void insert(node *x,node *y,int val,int d){
	if(d<0){
		if(y)*x=*y;x->sum++;
		return;
	}
	int v=val>>d&1;
	x->c[v]=new node();
	if(c(y,v))*x->c[v]=*c(y,v);x->siz++;
	x->c[!v]=c(y,!v);
	insert(c(x,v),c(y,v),val,d-1);
	x->rz();
}
int Q(int U,int D,int L,int R,int K){
	vector<int>vec;
	for(int i=U;i<=D;i++)
	for(int j=L;j<=R;j++)
	vec.push_back(a[i]^b[j]);
	sort(vec.begin(),vec.end());
	return vec[vec.size()-K];
}
int main(){
	freopen("bzoj4103.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=n;i++)a[i]=in();
	for(int i=1;i<=m;i++)b[i]=in();	
	q=in();
	while(q--){
		int u=in(),d=in(),l=in(),r=in(),k=in();
		printf("%d\n",Q(u,d,l,r,k));
	}
	return 0;
}
