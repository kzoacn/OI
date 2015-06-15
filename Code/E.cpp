#include<bits/stdc++.h>
using namespace std;
const int mo=1e9+7;
//typedef long long LL;
int n,q;
char s[5001];
int anss[5001];
//int fac[5001],inv[5001];
int C[5001][5001];
/*LL C(int n,int m){
	return (LL)fac[n]*inv[m]%mo*inv[n-m]%mo;
}*/
void getstr(char *s){
	char c=getchar();
	while(!isalpha(c))c=getchar();
	while(isalpha(c))*s++=c,c=getchar();
}
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
void pre(int n){
	register int i,j;
	C[0][0]=1;
	for(i=1;i<=n;i++){
		C[i][0]=1;
		for(j=1;j<=i;j++){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			if(C[i][j]>=mo)C[i][j]-=mo;	
		}			
	}
}
int tot;
int son[5001*5001/2][26];
short val[5001*5001];
void insert(int l){
	register int u=0;
	register int i;
	for(i=l;i<=n;i++){
		int v=s[i]-'a';
		if(!son[u][v])son[u][v]=++tot;
		u=son[u][v];val[u]++;
	}
}
void bfs(){
	register int u,i;
	queue<int>q;q.push(0);
	while(!q.empty()){
		u=q.front();q.pop();
		for(i=1;i<=val[u];i++){
			anss[i]=(anss[i]+C[val[u]][i]);
			while(anss[i]>=mo)anss[i]-=mo;
		}for(i=0;i<26;i++)if(son[u][i])q.push(son[u][i]);
	}
}
void put(int x){
	if(x<10)putchar(x+'0');
	else{
		put(x/10);
		putchar(x%10+'0');
	}
}
void sol(){
	scanf("%d%d",&n,&q);
	pre(n);tot=0;
	if(n<=5)memset(anss,0,sizeof anss);
	getstr(s+1);
	for(int i=1;i<=n;i++)insert(i);
	bfs();
	while(q--){
		int k=in();
		if(k>n)puts("0");
		else put(anss[k]),puts("");
	}if(n<=5)for(int i=0;i<=tot;i++)val[i]=0,memset(son[i],0,sizeof son[i]);
}

int main(){
	freopen("E.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
} 
