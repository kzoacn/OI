#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,m;
int a[maxn];
int all;
int getint(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
int fa[maxn];
int find(int x){if(fa[x]==x)return x;return fa[x]=find(fa[x]);}
map<int,int>ML;
struct Set{
	int all,size;
	map<int,int>M;
	int getMx(){return (--M.end())->first+all;}
	void insert(int x){M[x-all]++;size++;}
	void del(int x){if(!--M[x-all])M.erase(M[x-all]);size--;}
	void join(Set &oth){
		int mx;
		if(!--ML[mx=oth.getMx()])ML.erase(mx);
		if(!--ML[mx=getMx()])ML.erase(mx);
		while(oth.size){			
			insert(mx=oth.getMx());
			oth.del(mx);
		}ML[getMx()]++;
	}
}S[maxn];
Set* b[maxn];
int get(int x){return a[x]+b[x]->all;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)a[i]=getint(),fa[i]=i,b[i]=&S[i],b[i]->insert(a[i]),ML[a[i]]++;
	m=getint();
	while(m--){
		char op[3];scanf("%s",op);
		if(op[0]=='U'){
			int x=find(getint()),y=find(getint());
			if(x==y)continue;
			if(b[x]->size<b[y]->size)swap(x,y);
			b[x]->join(*b[y]);fa[y]=x;
		}else if(op[0]=='A'){
			if(op[1]=='1'){
				int x=getint(),y=getint();
				b[find(x)]->del(a[x]);
				b[find(x)]->insert(a[x]+=y);
				
				a[x]+=y;
			}else if(op[1]=='2'){
			
			}else{
			
			}
		}else{
			if(op[1]=='1'){
			
			}else if(op[1]=='2'){
			
			}else{
			
			}
		}
	}
	return 0;
}
