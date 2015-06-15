#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define ok(x) ((((x)>>bit+1)|ans)==ans&&((x)>>bit&1)==0)
LL s[2333];
int n,A,B;
void sol1(){
	static int g[2333];
	LL ans=0,res=0;int bit=0,i,j,k;
    while((1LL<<bit)<s[n])bit++;
    for(;bit>=0;bit--){
        for(i=1;i<=n;i++)
        for(g[i]=n+1,k=0;k<i;k++)
        if(ok(s[i]-s[k])&&g[i]>g[k]+1)g[i]=g[k]+1;
        ans=ans<<1|(g[n]>B);
    }
    cout<<ans<<endl;
}
void sol2(){
	static int f[101][101];
	LL ans=0;int bit=0;
	while((1LL<<bit)<s[n])bit++;
	for(;bit>=0;bit--){
		f[0][0]=1;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=min(i,B);j++){
			f[i][j]=0;
			for(int k=0;k<i&&!f[i][j];k++)
			if(f[k][j-1]&&ok(s[i]-s[k]))f[i][j]=1;
		}int flag=1;
		for(int j=A;j<=B;j++)if(f[n][j])flag=0;
		ans=ans<<1|flag;
	}cout<<ans<<endl;
}
int main(){
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		s[i]=s[i-1]+x;
	}	
	if(A==1)sol1();
	else sol2();
	return 0;
}
