#include<bits/stdc++.h>
using namespace std;
int n,m;
struct ufset{
	int fa[2001];
	void init(){for(int i=1;i<=n;i++)fa[i]=i;}
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
	void merge(int x,int y){fa[find(x)]=find(y);}
}f[3];
int kn[2001][2001];
int ans=0;
void check(int x){
	for(int i=1;i<=n;i++)if(i!=x){
		if(f[1].find(x)==f[1].find(i)
			&&f[2].find(x)==f[2].find(i)){
			if(!kn[i][x]){
				kn[i][x]=kn[x][i]=1;
				ans++;
			}	
		}
	}
}
void sol(){
	ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		kn[i][j]=0;
	f[1].init();f[2].init();
	long long sum=0;
	for(int i=1;i<=m;i++){
		int t,x,y;
		scanf("%d%d%d",&t,&x,&y);
		f[t].merge(x,y);
		for(int i=1;i<=n;i++)check(i);
		sum+=(long long)ans*i;
		//cerr<<ans<<endl;
		sum%=int(1e9+7); 
	}cout<<sum<<endl;
}
int main(){
	freopen("f1.in","r",stdin);
	freopen("f1.out","w",stdout);
	int T;scanf("%d",&T);	
	while(T--)sol(),cerr<<T<<endl;
	return 0;
}
