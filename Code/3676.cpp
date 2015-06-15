#include<cstdio>
#include<cstring>
const int M = 700050;
const int MAXM = 2100000;
const int inf = 987654321;
char data[M];
int sa[M],rank[MAXM],sab[M];
int val[M],valb[M];
int cc[M];
int height[MAXM],h[M],MT;
int n,m;
int tree[M];
struct XuA
{
    int l,r;
}xua[M],ja[M];
int ca;
struct XuB
{
    int l,r;
    int xi;
}xub[M],jb[M];
int cb=0;
int duix[M],duiy[M],top,tail;
void GetData()
{
    int i;
    scanf("%s",data+1);
    n=m=strlen(data+1);
    data[++n]='@';
    for(i=m;i>0;i--)
        data[++n]=data[i];
    data[n+1]=0;
}
void Suffix()
{
    int i,j,p;
    for(i=1;i<=n;i++)
        cc[data[i]]++;
    for(i=1;i<='z';i++)
        cc[i]+=cc[i-1];
    for(i=1;i<=n;i++)
    {
        rank[i]=cc[data[i]]--;
        sa[rank[i]]=i;
        val[i]=data[i];
    }
    p=1;
    for(i=1;i<n;i++)
    {
        if(val[sa[i]]==val[sa[i+1]])
            val[sa[i]]=p;
        else
        {
            val[sa[i]]=p;
            p++;
        }
    }
    val[sa[n]]=p;
    for(i=0;i<='z';i++)
        cc[i]=0;
    for(i=1;p<n;i<<=1)
    {
        for(j=1;j+i<=n;j++)
            valb[j]=val[j+i];
        memset(valb+j,0,(n<<2)-(j<<2)+4);
        for(j=1;j<=n;j++)
            cc[valb[j]]++;
        for(j=1;j<=p;j++)
            cc[j]+=cc[j-1];
        for(j=1;j<=n;j++)
            sab[cc[valb[j]]--]=j;
        memset(cc,0,(p<<2)+4);
        for(j=1;j<=n;j++)
            cc[val[j]]++;
        for(j=1;j<=p;j++)
            cc[j]+=cc[j-1];
        for(j=n;j>=1;j--)
            sa[cc[val[sab[j]]]--]=sab[j];
        memset(cc,0,(p<<2)+4);
        for(j=1;j<=n;j++)
            rank[sa[j]]=j;
        p=1;
        for(j=1;j<n;j++)
        {
            if(val[sa[j]]==val[sa[j+1]] && valb[sa[j]]==valb[sa[j+1]])
                val[sa[j]]=p;
            else
            {
                val[sa[j]]=p;
                p++;
            }
        }
        val[sa[n]]=p;
    }
    MT=1;
    while(MT<n+5)
        MT<<=1;
    for(i=1;i<=n;i++)
    {
        if(rank[i]==1)
            continue;
        h[i]=h[i-1]>0?h[i-1]-1:0;
        while(data[i+h[i]]==data[sa[rank[i]-1]+h[i]])
            h[i]++;
        height[rank[i]+MT]=h[i];
    }
    for(i=MT-1;i>0;i--)
        height[i]=height[i<<1]<height[(i<<1)|1]?height[i<<1]:height[(i<<1)|1];
}
int findmin(int l,int r)
{
    l+=MT-1;
    r+=MT+1;
    int minz=inf;
    int ll=l;
    int rr=r;
    while(ll^rr^1)
    {
        if(ll%2==0 && minz>height[ll^1])
            minz=height[ll^1];
        if(rr%2==1 && minz>height[rr^1])
            minz=height[rr^1];
        ll>>=1;
        rr>>=1;
    }
    while(l^r^1)
    {
        if(l%2==0 && height[l^1]==minz)
        {
            l^=1;
            break;
        }
        if(r%2==1 && height[r^1]==minz)
        {
            l=r^1;
            break;
        }
        l>>=1;
        r>>=1;
    }
    while(l<MT)
    {
        l<<=1;
        if(height[l]>height[l^1])
            l^=1;
    }
    l-=MT;
    return l;
}
void add(int x)
{
    while(x<=n)
    {
        tree[x]++;
        x+=(x&(-x));
    }
}
int find(int x)
{
    int res=0;
    while(x)
    {
        res+=tree[x];
        x-=(x&(-x));
    }
    return res;
}
void GetAns()
{
    int i,point;
    top=0;tail=1;
    duix[1]=1;duiy[1]=n;
    while(top<tail)
    {
        top++;
        int l=duix[top];
        int r=duiy[top];
        int now=findmin(l+1,r);
        cb++;
        jb[cb].l=l;
        jb[cb].r=r;
        jb[cb].xi=height[now+MT];
        if(l<now-1)
        {
            tail++;
            duix[tail]=l;
            duiy[tail]=now-1;
        }
        if(now<r)
        {
            tail++;
            duix[tail]=now;
            duiy[tail]=r;
        }
    }
    for(i=1;i<=cb;i++)
        cc[jb[i].l]++;
    for(i=n;i>=1;i--)
        cc[i]+=cc[i+1];
    for(i=1;i<=cb;i++)
        xub[cc[jb[i].l]--]=jb[i];
    for(i=1;i<=n;i++)
        cc[i]=0;
    long long ans=0,now;
    ca=0;
    for(i=1;i<=m;i++)
    {
        ca++;
        ja[ca].l=rank[i];
        ja[ca].r=rank[n-i+1];
        if(ja[ca].l>ja[ca].r)
        {
            ja[ca].l^=ja[ca].r;
            ja[ca].r^=ja[ca].l;
            ja[ca].l^=ja[ca].r;
        }
    }
    for(i=1;i<=ca;i++)
        cc[ja[i].l]++;
    for(i=n;i>=1;i--)
        cc[i]+=cc[i+1];
    for(i=1;i<=ca;i++)
        xua[cc[ja[i].l]--]=ja[i];
    for(i=1;i<=n;i++)
        cc[i]=0;
    point=1;
    for(i=1;i<=cb;i++)
    {
        while(point<=ca && xua[point].l>=xub[i].l)
        {
            add(xua[point].r);
            point++;
        }
        now=find(xub[i].r);
        now*=(xub[i].xi*2-1);
        if(ans<now)
            ans=now;
    }
    ca=0;
    for(i=2;i<=m;i++)
    {
        ca++;
        ja[ca].l=rank[i];
        ja[ca].r=rank[n-i+2];
        if(ja[ca].l>ja[ca].r)
        {
            ja[ca].l^=ja[ca].r;
            ja[ca].r^=ja[ca].l;
            ja[ca].l^=ja[ca].r;
        }
    }
    for(i=1;i<=ca;i++)
        cc[ja[i].l]++;
    for(i=n;i>=1;i--)
        cc[i]+=cc[i+1];
    for(i=1;i<=ca;i++)
        xua[cc[ja[i].l]--]=ja[i];
    for(i=1;i<=n;i++)
        cc[i]=0;
    memset(tree,0,(n<<2)+4);
    point=1;
    for(i=1;i<=cb;i++)
    {
        while(point<=ca && xua[point].l>=xub[i].l)
        {
            add(xua[point].r);
            point++;
        }
        now=find(xub[i].r);
        now*=(xub[i].xi<<1);
        if(ans<now)
            ans=now;
    }
    printf("%lld\n",ans);
}
int main()
{
    GetData();
    Suffix();
    GetAns();
    return 0;
}
