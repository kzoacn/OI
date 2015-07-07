#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<stack>

const int MAXN = 1010;
const int mod = 10007;
int n;
char clr[MAXN][MAXN];
int h[MAXN],table[MAXN][MAXN];
int ans[MAXN][MAXN],up[MAXN][MAXN],down[MAXN][MAXN];
int up1[MAXN][MAXN],up2[MAXN][MAXN],down1[MAXN][MAXN],down2[MAXN][MAXN];
int st[1001000],top;

using namespace std;

int read()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}

void swap_ver(int ret[MAXN][MAXN])
{
     for (int i=1;i<=n;i++)
         for (int j=1,k=n;j<k;j++,k--)
             swap(ret[i][j],ret[i][k]);
}
void swap_hor(int ret[MAXN][MAXN])
{
     for (int j=1,k=n;j<k;j++,k--)
         for (int i=1;i<=n;i++)
             swap(ret[j][i],ret[k][i]);
}
void calc(int ret[MAXN][MAXN])
{
     for (int i=1;i<=n;i++)
         for (int j=1;j<=n;j++)
         {
             ret[i][j]=ret[i][j]+ret[i-1][j]+ret[i][j-1]-ret[i-1][j-1];
             ret[i][j]=(ret[i][j]+mod)%mod;
         }
}
void copy(int a[MAXN][MAXN],int b[MAXN][MAXN])
{
     for (int i=1;i<=n;i++)
         for(int j=1;j<=n;j++)
             a[i][j]=b[i][j];
}
void solve()
{   
    for (int i=1;i<=n;i++) h[i]=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            if ( table[i][j] ) ++h[j];
            else h[j]=0;
        }
        stack<int> stk;
        stk.push(0);
        int ret=0;
        for (int j=1;j<=n;j++)
        {
            while (stk.top() && h[stk.top()]>=h[j])
            {
                int a=stk.top(); stk.pop();
                int b=stk.top();
                ret-=(j-b-1)*(h[a]-max(h[j],h[b]));
            }
            stk.push(j);  ret+=h[j];
            ans[i][j]=max(ret-1,0)%mod;
        }
    }  
}

int main() 
{
    freopen("rect.in","r",stdin);
    freopen("rect.out","w",stdout);
    n=read();
    for (int i=0;i<n;i++)
    {
        scanf("%s",clr[i]);
        for (int j=0;j<n;j++)
            table[i+1][j+1]=(clr[i][j]=='C');
    }
    solve();
    copy(up,ans);
    copy(up1,ans);
    calc(up1); swap_ver(table); solve();
    copy(up2,ans);
    calc(up2); swap_ver(table); swap_hor(table); solve(); 
    copy(down,ans);
    copy(down1,ans);
    calc(down1); swap_ver(table); solve();
    copy(down2,ans);
    calc(down2); 
    swap_ver(up2); swap_hor(down); swap_hor(down1); swap_ver(down2); swap_hor(down2);
    int ans=0;
    for (int i=1;i<=n;i++)
    {
         ans += ( down1[1][i]-down1[1][i-1]+mod ) * down2[1][i+1];
         ans += ( up1[i][n]-up1[i-1][n]+mod ) * down1[i+1][n];
         ans %= mod;
         for( int j = 1; j <= n; ++j ) 
         {
              ans -= up[i][j] * down2[i+1][j+1];
              ans -= down[i][j] * up2[i-1][j+1];
              ans = ( ans%mod + mod ) % mod;
         }
    }
    printf("%d\n",ans); 
    return 0;
}
