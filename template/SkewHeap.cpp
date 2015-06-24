#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int fa[maxn],n,m;
int find(int x){
	if(fa[x]!=x)return fa[x]=find(fa[x]);
	return x;
}
bool die[maxn];
struct node;
node *Null,*root[maxn];
struct node{
	node* c[2];
	int val,ind;
	node(int _val=0,int _ind=0){
		val=_val;c[0]=c[1]=Null;ind=_ind;
	}
};
node* merge(node *p,node *q){
	if(p==Null)return q;
	if(q==Null)return p;
	if(p->val>q->val)swap(p,q);
	p->c[1]=merge(p->c[1],q);
	swap(p->c[0],p->c[1]);
	return p;
}
void deb(node *x){
	if(x==Null)return;
	printf("%d ",x->val);
	deb(x->c[0]);
	deb(x->c[1]);
}
int main(){
	scanf("%d",&n);
	Null=new node(0);
	Null->c[0]=Null->c[1]=Null;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		root[i]=new node(x,i);
	}scanf("%d",&m);
	while(m--){
		char opt[2];
		scanf("%s",&opt);
		if(opt[0]=='M'){
			int a,b;scanf("%d%d",&a,&b);
			if(die[a]||die[b])continue;
			a=find(a);b=find(b);
			if(a==b)continue;
			root[a]=root[b]=merge(root[a],root[b]);
			
			fa[find(b)]=find(a);
		}else{
			int x;scanf("%d",&x);
			if(die[x]||root[find(x)]==Null)
				puts("0");
			else{
				x=find(x);
				die[root[x]->ind]=1;
				printf("%d\n",root[x]->val);
				root[x]=merge(root[x]->c[0],root[x]->c[1]);
			}
						
		}
	}
	return 0;
}
