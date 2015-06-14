#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;
const int mo=20130426;
typedef long long LL;
struct flag{
	int mul,add;
	flag(){mul=1;add=0;}
	flag(int mul,int add):mul(mul),add(add){}
	void cl(){mul=1;add=0;}
	bool em(){return mul==1&&add==0;}
};
flag operator+(flag A,flag B){return flag((LL)A.mul*B.mul%mo,((LL)A.mul*B.add+A.add)%mo);}
int operator+(flag A,int B){return ((LL)A.mul*B+A.add)%mo;}
struct node{
	int key;
	int val,siz;flag fl;
	node(){}
	node *c[2],*f;
	node *rz(){siz=1;if(c[0])siz+=c[0]->siz;if(c[1])siz+=c[1]->siz;return this;}
	void pd(){
		if(fl.em())return;
		if(c[0])c[0]->val=fl+c[0]->val,c[0]->fl=fl+c[0]->fl;
		if(c[1])c[1]->val=fl+c[1]->val,c[1]->fl=fl+c[1]->fl;
		fl.cl();
	}
	void split(int ned,node *&p,node *&q);
}nd[maxn],*root;
node *merge(node *p,node *q){
	if(!p||!q)return p?p->rz():(q?q->rz():0);
	p->pd();q->pd();
	if(p->key<q->key){
		p->c[1]=merge(p->c[1],q);
		return p->rz();
	}else{
		q->c[0]=merge(p,q->c[0]);
		return q->rz();
	}
}
#define sz(x) (x?x->siz:0)
void node::split(int ned,node *&p,node *&q){
	if(!ned){p=0;q=this;return;}
	if(ned==siz){p=this;q=0;return;}
	pd();
	if(sz(c[0])>=ned){
		c[0]->split(ned,p,q);c[0]=0;rz();
		q=merge(q,this);
	}else{
		c[1]->split(ned-sz(c[0])-1,p,q);c[1]=0;rz();
		p=merge(this,p);
	}
}
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m;
vector<int>vec;
void dfs(node *t){
	t->pd();
	if(t->c[0])dfs(t->c[0]);
	vec.push_back(t->val);
	if(t->c[1])dfs(t->c[1]);
}
void deb(node *t){
	if(t->c[0])deb(t->c[0]);
	printf("%d ",t->val);
	if(t->c[1])deb(t->c[1]);
}
int Q(int v){
	vec.clear();
	int ans=0;dfs(root);
	for(int i=vec.size()-1;i>=0;i--)
		ans=((LL)ans*v+vec[i])%mo;
	return ans;
}
void Mulx(int l,int r){
	l++;r++;
	node *p,*q,*x,*y,*z,*w,*a,*b;
	root->split(l-1,p,q);
	q->split(r-l,x,y);
	y->split(1,z,w);
	w->split(1,a,b);	
	z->val=(z->val+a->val)%mo;
	a->val=0;
	//root=merge(p,a,x,z,b);
	root=merge(merge(p,a),merge(x,merge(z,b)));
}
void C(int l,int r,flag f){
	l++;r++;
	node *p,*q,*x,*y;
//	deb(root);puts("");
	root->split(l-1,p,q);
//	deb(p);puts("");
	q->split(r-l+1,x,y);
//	deb(x);puts("");
	x->val=(f+x->val)%mo;
	x->fl=f+x->fl;
	x->pd();
	root=merge(p,merge(x,y));
}
int main(){
	freopen("bzoj3323.in","r",stdin);
	m=in();
	//for(int i=1;i<=2e5;i++)root=merge(root,nd+i);
	for(int i=1;i<=1e5+5;i++){
		nd[i].key=rand();
		root=merge(root,nd+i);
	}
	while(m--){
		char op[5];scanf("%s",op);
		int l,r,v;
		if(strlen(op)==4){
			l=in();r=in();
			Mulx(l,r);
		}else if(op[0]=='q'){
			printf("%d\n",Q(in()%mo));
		}else{
			l=in(),r=in();
			flag f;
			if(op[0]=='a')f=flag(1,in()%mo);
			else f=flag(in()%mo,0);
			C(l,r,f);
		}
	}
	return 0;
}
