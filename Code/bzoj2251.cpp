#include<bits/stdc++.h>
#define id(x) (x-'0')
using namespace std;
const int maxn=3001;
int n;char s[maxn]; 
struct node{
	int val;
	node *c[2];
	node(){val=0;c[0]=c[1]=0;}
}*root=new node();
void dfs(node *u){
	if(u->val>1)printf("%d\n",u->val);
	if(u->c[0])dfs(u->c[0]);
	if(u->c[1])dfs(u->c[1]);
}
int main(){
	scanf("%d%s",&n,s);
	for(int i=0;i<n;i++){
		node *u=root;
		for(int j=i;j<n;j++){
			int v=s[j]-'0';
			if(!u->c[v])u->c[v]=new node();
			u=u->c[v];
			u->val++;
		}
	}dfs(root);
	return 0;
}
