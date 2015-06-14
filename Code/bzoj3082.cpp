#include<stdio.h>
#include<string.h>
#include<ctype.h>
const int maxn=50010;
struct edge{int u,v; bool iscut,istree;};
int n,m;
int fa[maxn];
edge edges[200010];
int size;
int x,y,q,u,v;
char op;
inline int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int fa2[maxn];
void rebuild(){
	memcpy(fa,fa2,sizeof(int)*(n+1));
	int k=0;
	const edge *end=edges+size;
	for(register edge *i=edges+1;i<=end;i++){
		i->istree=0;
		if(!i->iscut){
			if(find(i->v)!=find(i->u)){
				k++;
				fa[fa[i->v]] = fa[i->u];
				i->istree=1;
				if(k==n-1)break;
			}
		}
	}
}
int main(){
	n=getint();m=getint();register int i;
	for(i=1;i<=n;i++)fa2[i]=i;
	for(i=1;i<=m;i++){
		u=getint(),v=getint();
		edges[++size]=(edge){u,v,0,0};
	}rebuild();
	q=getint();
	while(q--){
		op=getchar();while(!isalpha(op))op=getchar();
		if(op=='D'){
			edges[x=getint()].iscut=1;
			if(edges[x].istree)rebuild();
		}else if(op=='I'){
			x=getint();y=getint();
			edges[++size]=(edge){x,y,0,0};
			if(find(x)!=find(y))fa[fa[x]]=fa[y],edges[size].istree=1;
		}else x=getint(),y=getint(),puts(find(x)==find(y)?"Yes":"No");
	}
	return 0;
}
