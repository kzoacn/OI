#include<bits/stdc++.h>
using namespace std;
const int maxn=501;
int f[2][maxn][maxn];
int a[maxn];
int n,m,b,mo;
void up(int &x,int y){x+=y;if(x>=mo)x-=mo;}
int main(){
    scanf("%d%d%d%d",&n,&m,&b,&mo);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    f[0][0][0]=1;
    int cur=0;
    for(int i=1;i<=n;i++){
        cur^=1;
        memset(&f[cur][0][0],0,sizeof(int)*maxn*maxn);
        for(int j=0;j<=m;j++)
        for(int k=0;k<=b;k++)
        for(int l=0;l<=j&&k-a[i]*l>=0;l++){
    //      cerr<<f[i-1][j-l][k-a[i]*l]<<endl;
            up(f[cur][j][k],f[cur^1][j-l][k-a[i]*l]);
    //      cerr<<f[i][j][k]<<endl;
        }
    }
    int ans=0;
    for(int i=0;i<=b;i++)up(ans,f[cur][m][i]);
    cout<<ans<<endl;
    return 0;
}
