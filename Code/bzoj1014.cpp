#include<bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
const int maxn=1e5+5;
int rnd(){return rand();}
UL hash_l[maxn];
int len;
struct node{
	int key,size;
	int val;
	UL hash;
	node *c[2];
	node* rz(){
		size=1;hash=0;
		if(c[0])hash=c[0]->hash,size+=c[0]->size;
		hash=hash*hash_l[1]+val;
		if(c[1])hash=hash*hash_l[c[1]->size]+c[1]->hash,size+=c[1]->size;
		return this;
	}
	void split(int ned,node *&p,node *&q);
}*root,pool[maxn],*cur=pool+1;
node *newnode(int val){
	node *x=cur++;
	x->key=rnd();
	x->val=val;
	return x;
}
node *merge(node *p,node *q){
	if(!p||!q)return p?p->rz():(q?q->rz():q);
//	p->pd();q->pd();
	if(p->key<q->key){
		p->c[1]=merge(p->c[1],q);
		return p->rz();	
	}else{
		q->c[0]=merge(p,q->c[0]);
		return q->rz();		
	}
}
void node::split(int ned,node *&p,node *&q){
	if(!ned){p=0;q=this;return;}
//	pd();
	if(c[0]&&c[0]->size>=ned){
		if(c[0])c[0]->split(ned,p,q);
		else p=q=0;c[0]=0;rz();
		q=merge(q,this);
	}else{
		if(c[1])c[1]->split(ned-(c[0]?c[0]->size:0)-1,p,q);
		else p=q=0;c[1]=0;rz();
		p=merge(this,p);
	}
}
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
char getA(){
	char c=getchar();
	while(!isalpha(c))c=getchar();
	return c;
}
char s[maxn];
UL gethash(int l,int r){
	UL ans=0;
	node *p,*q,*x,*y;
	root->split(l-1,p,q);
	q->split(r-l+1,x,y);
	ans=x->hash;
	q=merge(x,y);
	root=merge(p,q);
	return ans;
}
void deb(node *x){
	if(x->c[0])deb(x->c[0]);
	printf("%c",x->val+'a');
	//printf("id:%d val:%c c[0]:%d c[1]:%d\n",x-pool,x->val+'a',
	//	x->c[0]?x->c[0]-pool:0,x->c[1]?x->c[1]-pool:0);
	if(x->c[1])deb(x->c[1]);
}
int Q(int x,int y){
	int l=1,r=min(len-x+1,len-y+1)+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(gethash(x,x+mid-1)==gethash(y,y+mid-1))
			l=mid+1;
		else r=mid;
	}return l-1;
}
int main(){
	hash_l[0]=1;
	for(int i=1;i<maxn;i++)hash_l[i]=hash_l[i-1]*31;
	char c=getchar();
	while(isalpha(c))s[len++]=c,c=getchar();
	for(int i=0;i<len;i++)
		root=merge(root,newnode(s[i]-'a'));
	int m=getint();
	while(m--){
//		deb(root);puts("");
		char op=getA();
		if(op=='Q'){
			int x=getint(),y=getint();
			printf("%d\n",Q(x,y));
		}else if(op=='I'){
			node *p,*q;
			int x=getint();char c=getA();
			root->split(x,p,q);
			q=merge(newnode(c-'a'),q);
			root=merge(p,q);
			len++;
		}else if(op=='R'){
//			deb(root);puts("");
			node *p,*q,*r,*s;
			int x=getint();char c=getA();
			root->split(x-1,p,q);
//			deb(p);puts("");
//			deb(q);puts("");
			q->split(1,r,s);
//			deb(r);puts("");
//			deb(s);puts("");
			r->val=c-'a';r->rz();
			q=merge(r,s);
			root=merge(p,q);
//			deb(root);	
		}
	}
	return 0;
}
