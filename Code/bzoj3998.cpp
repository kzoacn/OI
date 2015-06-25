#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int go[maxn][26],tot=1,root=1,last=1,val[maxn],fa[maxn];
int newnode(int x){
	val[++tot]=x;
	return tot;
}
int n,ty,K;
void add(int w){
	int p=last;
	int np=newnode(val[p]+1);
	while(p&&!son[p][w])son[p][w]=np,p=fa[p];
	if(!p)fa[np]=root;
	else{
		int q=son[p][w];
		if(val[p]+1==val[q])fa[np]=q;
		else{
			int nq=newnode(val[p]+1);
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[np]=nq;fa[nq]=p;
		}
	}
	last=np;
}
int main(){

	return 0;
}
