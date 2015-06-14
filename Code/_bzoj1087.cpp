#include<iostream>
#include<cstdio>
using namespace std;
int n,m,all,cnt[512];
long long f[10][100][512];
bool c1[512],c2[512][512];
long long ans;
void pre()
{
     int s;
     for(int i=0;i<=all;i++)
        if((i&(i>>1))==0)
           {
           s=0;
           for(int x=i;x;x>>=1)s+=(x&1);
           cnt[i]=s;c1[i]=1;
           }
     for(int i=0;i<=all;i++)if(c1[i])
        for(int j=0;j<=all;j++)if(c1[j])
           if(((i&j)==0)&&((i&(j>>1))==0)&&((j&(i>>1))==0))
              c2[i][j]=1;
     }
int main()
{
    scanf("%d%d",&n,&m);
    all=(1<<n)-1;
    pre();
    for(int i=0;i<=all;i++)if(c1[i])f[1][cnt[i]][i]=1;
    for(int j=1;j<n;j++)
       for(int k=0;k<=all;k++)if(c1[k])
          for(int i=0;i<=all;i++)if(c1[i])
             if(c2[k][i])
                for(int p=cnt[k];p+cnt[i]<=m;p++)
                    f[j+1][p+cnt[i]][i]+=f[j][p][k];
    long long ans=0;
    for(int i=0;i<=all;i++)ans+=f[n][m][i];
    printf("%lld",ans);
    return 0;
    }
