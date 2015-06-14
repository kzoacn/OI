#include<cstdio>

#include<cstdlib>

#include<cmath>

#include<cstring>

#include<algorithm>

#include<iostream>

#include<vector>

#include<map>

#include<set>

#include<queue>

#include<string>

#define inf 1000000000

#define maxn 1000000+5

#define maxm 500+100

#define eps 1e-10

#define ll long long

#define pa pair<int,int>

#define for0(i,n) for(int i=0;i<=(n);i++)

#define for1(i,n) for(int i=1;i<=(n);i++)

#define for2(i,x,y) for(int i=(x);i<=(y);i++)

#define for3(i,x,y) for(int i=(x);i>=(y);i--)

#define mod 1000000007

using namespace std;

inline int read()

{

    int x=0,f=1;char ch=getchar();

    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}

    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}

    return x*f;

}
int n,next[maxn];
ll ans;
char s[maxn];

int main()

{

 
    n=read();
    scanf("%s",s+1);
    for(int i=2,j=0;i<=n;i++)
    {
        while(j&&s[j+1]!=s[i])j=next[j];
        if(s[j+1]==s[i])j++;
        next[i]=j;
    }
    for1(i,n)if(next[next[i]]!=0)next[i]=next[next[i]];
    for1(i,n)if(next[i])ans+=(ll)(i-next[i]);
    printf("%lld\n",ans);

    return 0;

}
