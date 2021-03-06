#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int n,m;
struct node;
node *Null,*root;
struct node{
    node* c[2];
    int val;
    node(int _val=0){
        val=_val;c[0]=c[1]=Null;
    }
};
int ran(){static int x=1;x+=(x<<2)+1; x&=(0x7fffffff);return x&1;}
node* merge(node *p,node *q){
    if(p==Null)return q;
    if(q==Null)return p;
    if(p->val>q->val)swap(p,q);
    if(ran())p->c[1]=merge(p->c[1],q);
    else p->c[0]=merge(p->c[0],q);
    return p;
}
void deb(node *x){
    if(x==Null)return;
    printf("%d ",x->val);
    deb(x->c[0]);
    deb(x->c[1]);
}
int main(){
    scanf("%d",&n);scanf("%d",&m);
    Null=new node(0);
    Null->c[0]=Null->c[1]=Null;
    root=Null;
    while(m--){
		int op;scanf("%d",&op);
		if(op==1){
			int x;scanf("%d",&x);
			root=merge(root,new node(x));
		}else
		if(op==2){
			root=merge(root->c[0],root->c[1]);
		}else printf("%d\n",root->val);
	}
    
    cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
    return 0;
}
