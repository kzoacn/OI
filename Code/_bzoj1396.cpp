#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 500100
#define inf 1000000000
using namespace std;
struct node
{
    node *ch[27],*pre;
    int len;
    bool v;
}sam[maxn*2],*rot,*now;
char s[maxn];
int n,m,num;
struct segtree
{
    int key[maxn*3],cov[maxn*3];
    void build(int x,int l,int r)
    {
        key[x]=cov[x]=inf;
        if (l==r) return ;
        int mid=(l+r)>>1;
        build(x*2,l,mid); build(x*2+1,mid+1,r);
    }
    void cover(int x,int z)
    {
        cov[x]=min(cov[x],z);
        key[x]=min(key[x],z);
    }
    void down(int x)
    {
        if (cov[x]==inf) return ;
        cover(x*2,cov[x]); cover(x*2+1,cov[x]);
        cov[x]=inf;
    }
    void add(int x,int l,int r,int ll,int rr,int z)
    {
        down(x);
        if (ll<=l&&r<=rr) cover(x,z);
        else
        {
            int mid=(l+r)>>1;
            if (ll<=mid) add(x*2,l,mid,ll,rr,z);
            if (rr>mid) add(x*2+1,mid+1,r,ll,rr,z);
            key[x]=min(key[x*2],key[x*2+1]);
        }
    }
    int ask(int x,int l,int r,int z)
    {
        down(x);
        if (l==r) return key[x];
        int mid=(l+r)>>1;
        if (z<=mid) return ask(x*2,l,mid,z);
        else return ask(x*2+1,mid+1,r,z);
    }
}S,T;

void insert(int w)
{
    node *p=now,*np=&sam[++num];
    np->len=p->len+1; np->v=1;
    while (p&&p->ch[w]==0) p->ch[w]=np,p=p->pre;
    if (!p) np->pre=rot;
    else
    {
        node *q=p->ch[w];
        if (p->len+1==q->len) np->pre=q;
        else
        {
            node *nq=&sam[++num];
            *nq=*q;
            nq->len=p->len+1; nq->v=0;
            np->pre=q->pre=nq;
            while (p&&p->ch[w]==q) p->ch[w]=nq,p=p->pre;
        }
    }
    now=np;
}

int main()
{
    scanf("%s",s);
    n=strlen(s);
    rot=now=&sam[num=0];
    for (int i=0;i<n;i++) insert(s[i]-'a');
    S.build(1,1,n);
    T.build(1,1,n);
    for (int i=1;i<=num;i++)
        sam[i].pre->v=0;
    for (int i=1;i<=num;i++) 
        if (sam[i].v==1)
        {
            node *p=&sam[i];
            int l=(p->len)-(p->pre->len),r=p->len;
            S.add(1,1,n,l,r,r-l+1);
            if (l>1) T.add(1,1,n,1,l-1,r);
        }
    for (int i=1;i<=n;i++)
        printf("%d\n",min(S.ask(1,1,n,i),T.ask(1,1,n,i)-i+1));
    return 0;
}
