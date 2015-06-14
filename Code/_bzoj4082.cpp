#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 1001001
using namespace std;
int len,n,ans=0x3f3f3f3f;
int fa[20][M],dpt[M];
struct Interval{
    int x,y;
    friend istream& operator >> (istream &_,Interval &i)
    {
        scanf("%d%d",&i.x,&i.y);
        if(i.y<i.x) i.y+=len;
        return _;
    }
    friend bool operator < (const Interval &i1,const Interval &i2)
    {
        return i1.y < i2.y ;
    }
}intervals[M];
bool Compare(int x,int y)
{
    return intervals[x] < intervals[y] ;
}
void Get_Depth(int x)
{
    if(!fa[0][x])
        dpt[x]=1;
    if(dpt[x])
        return ;
    Get_Depth(fa[0][x]);
    dpt[x]=dpt[fa[0][x]]+1;
}
void Build_LCA()
{
    int i,j;
    for(i=1;i<=n;i++)
        Get_Depth(i);
    for(j=1;j<=19;j++)
        for(i=1;i<=n;i++)
            fa[j][i]=fa[j-1][fa[j-1][i]];
}
int Query(int x,int limit)
{
    int j;
    for(j=19;~j;j--)
        if(fa[j][x]&&intervals[fa[j][x]].y<limit)
            x=fa[j][x];
    return intervals[x].y>=limit?x:fa[0][x];
}
int main()
{
    int i,j;
    cin>>len>>n;
    for(i=1;i<=n;i++)
        cin>>intervals[i];
    sort(intervals+1,intervals+n+1);
    static int max_y[M];
    for(i=1;i<=n;i++)
        max_y[intervals[i].x]=max(max_y[intervals[i].x],i);
    int temp=0;
    for(j=1,i=1;i<=n;i++)
    {
        for(;j<=intervals[i].y+1;j++)
            temp=max(temp,max_y[j],Compare);
        fa[0][i]=temp==i?0:temp;
    }
    Build_LCA();
    for(i=1;i<=n;i++)
    {
        int temp=Query(i,intervals[i].x+len-1);
        if(temp) ans=min(ans,dpt[i]-dpt[temp]+1);
    }
    if(ans==0x3f3f3f3f)
        puts("impossible");
    else
        cout<<ans<<endl;
    return 0;
}
