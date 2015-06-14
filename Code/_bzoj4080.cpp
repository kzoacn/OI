#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 110
using namespace std;
typedef bitset<M> abcd;
struct Point{
    int x,y;
    friend istream& operator >> (istream &_,Point &p)
    {
        return scanf("%d%d",&p.x,&p.y),_;
    }
    friend bool operator < (const Point &p1,const Point &p2)
    {
        return p1.x < p2.x ;
    }
    friend int Distance(const Point &p1,const Point &p2)
    {
        return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) ;
    }
}points[M];
int n,d;
abcd a[M];
abcd now,able,ans;
int main()
{
    int i,j;
    cin>>n>>d;
    for(i=1;i<=n;i++)
        cin>>points[i];
    for(i=1;i<=n;i++)
        for(j=i+1;j<=n;j++)
            if(Distance(points[i],points[j])<=d*d)
                a[i][j]=a[j][i]=true;
    static int order[M];
    for(i=1;i<=n;i++)
    {
        able[i]=true;
        order[i]=i;
    }
    for(j=1;j<=1000;j++)
    {
        abcd able=::able;
        now.reset();
        for(i=1;i<=n;i++)
            if(able[order[i]])
            {
                now[order[i]]=true;
                able&=a[order[i]];
            }
        if(now.count()>ans.count())
            ans=now;
        random_shuffle(order+1,order+n+1);
    }
    cout<<ans.count()<<endl;
    for(i=1;i<=n;i++)
        if(ans[i])
           printf("%d ",i);
    return 0;
}
