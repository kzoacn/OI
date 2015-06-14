#include<bits/stdc++.h>
#define idx(c) (c-'a')
using namespace std;
const int maxn=205;
const int maxlen=1e6+205;
int n,len,anss[maxn];
char s[maxlen],str[maxlen];
struct node{
	vector<int>val;
	node *go[27],*fail,*last;
	node(node *C=0){
		for(int i=0;i<27;i++)go[i]=C;
		fail=last=C;
	}
}*root,*Null;
void insert(const char *s,int x){
	node *u=root;int len=strlen(s);
	for(int i=0;i<len;i++){
		int v=idx(s[i]);
		if(u->go[v]==Null)u->go[v]=new node(Null);
		u=u->go[v];
	}u->val.push_back(x);
}
void get_fail(){
	queue<node*>q;
	for(int i=0;i<27;i++)if(root->go[i]!=Null)
	q.push(root->go[i]),root->go[i]->fail=root->go[i]->last=root;
	while(!q.empty()){
		node *u=q.front(),*v;q.pop();
		for(int i=0;i<27;i++)if((v=u->go[i])!=Null){
			q.push(v);node *j=u->fail;
			while(j!=Null&&j->go[i]==Null)j=j->fail;
			v->fail=j->go[i];
			v->last=v->fail->val.size()?v->fail:v->fail->last;
		}
	}
}
void calc(node *j){
	for(int i=0;i<j->val.size();i++)
	anss[j->val[i]]++;
	if(j->last!=Null)calc(j->last);
}
void find(){
	node *j=root;
	for(int i=0;i<len;i++){
		int v=idx(str[i]);
		while(j!=Null&&j->go[v]==Null)j=j->fail;
		j=j->go[v];
		if(j->val.size())calc(j);
		else if(j->last!=Null)calc(j->last);		
	}	
}
int main(){
	Null=new node();root=Null;
	for(int i=0;i<27;i++)Null->go[i]=Null;
	Null->fail=Null->last=Null;	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);copy(s,s+strlen(s),str+len);len+=strlen(s);str[len++]='{';
		insert(s,i);
	}get_fail();
	find();
	for(int i=1;i<=n;++i)printf("%d\n",anss[i]);
	return 0;
}
