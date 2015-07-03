#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
using namespace std;
#define MAXN 51000
#define MAXV MAXN
#define MAXE MAXV*2
#define MAXT MAXN*40
#define INF 0x3f3f3f3f
#define smid ((l+r)>>1)
int n,m;
struct aaa
{
        int x,l,r;
        int lv;
        pair<int,int> mx;
};
bool operator < (const aaa& a1,const aaa& a2)
{
        return a1.mx<a2.mx;
}
struct sgt_node
{
        int lc,rc;
        pair<int,int> mx;
}sgt[MAXT];
int topt=0;
void Build_sgt(int &now,int l,int r,int v[])
{
        now=++topt;
        if (l==r)
        {
                sgt[now].mx=make_pair(v[l],l);
                return ;
        }
        Build_sgt(sgt[now].lc,l,smid,v);
        Build_sgt(sgt[now].rc,smid+1,r,v);
        if (sgt[sgt[now].lc].mx>sgt[sgt[now].rc].mx)
                sgt[now].mx=sgt[sgt[now].lc].mx;
        else
                sgt[now].mx=sgt[sgt[now].rc].mx;
}
pair<int,int> Query_sgt(int &now,int l,int r,int x,int y)
{
        if (l==x && r==y)
                return sgt[now].mx;
        if (y<=smid)
                return Query_sgt(sgt[now].lc,l,smid,x,y);
        else if (smid<x)
                return Query_sgt(sgt[now].rc,smid+1,r,x,y);
        else
                return max(Query_sgt(sgt[now].lc,l,smid,x,smid),Query_sgt(sgt[now].rc,smid+1,r,smid+1,y));

}

struct Edge
{
        int np,val;
        int id;
        Edge *next;
}E[MAXE],*V[MAXV];
int tope=-1;
void addedge(int x,int y,int z,int id)
{
        E[++tope].np=y;
        E[tope].val=z;
        E[tope].id=id;
        E[tope].next=V[x];
        V[x]=&E[tope];
}
int elev[MAXE];
int pnt[MAXN];
int q[MAXN];
int siz[MAXN];
int get_core(int now)
{
        Edge *ne;
        int head=-1,tail=0;
        q[0]=now;
        pnt[now]=now;
        while (head<tail)
        {
                now=q[++head];
                for (ne=V[now];ne;ne=ne->next)
                {
                        if (ne->np==pnt[now] || ~elev[ne->id])continue;
                        q[++tail]=ne->np;
                        pnt[ne->np]=now;
                }
        }
        for (register int i=tail;i>=0;i--)
        {
                now=q[i];
                siz[now]=1;
                for (ne=V[now];ne;ne=ne->next)
                {
                        if (ne->np==pnt[now] || ~elev[ne->id])continue;
                        siz[now]+=siz[ne->np];
                }
        }
        int ret;
        int mxsiz=0,bstsiz=INF;
        if (siz[q[0]]==1)return -1;
        for (register int i=0;i<=tail;i++)
        {
                now=q[i];
                mxsiz=siz[q[0]]-siz[now];
                for (ne=V[now];ne;ne=ne->next)
                {
                        if (ne->np==pnt[now] || ~elev[ne->id])continue;
                        mxsiz=max(mxsiz,siz[ne->np]);
                }
                if (bstsiz>mxsiz)
                {
                        bstsiz=mxsiz;
                        ret=now;
                }
        }
        return ret;
}
int seq[20][MAXN];
int cdis[20][MAXN];
int totsq[20];
int stack[MAXN],tops=-1;
void dfs1(int now,int dist,int lev,int p)
{
        register Edge *ne;
        seq[lev][totsq[lev]]=now;
        cdis[lev][totsq[lev]]=dist;
        totsq[lev]++;
        stack[++tops]=now;
        for (ne=V[now];ne;ne=ne->next)
        {
                if (~elev[ne->id] || ne->np==p)continue;
                dfs1(ne->np,dist+ne->val,lev,now);
        }
}
aaa stacka[MAXN*40];
int topsa=-1;
void solve(int now,int lev)
{
        int core=get_core(now);
        int tsiz=siz[q[0]];
        if (tsiz==1)return ;
        register Edge *ne;
        for (ne=V[core];ne;ne=ne->next)
                if (elev[ne->id]==-1)
                        elev[ne->id]=lev;
        int a,b;
        aaa at;
        at.lv=lev;
        a=totsq[lev];
        seq[lev][totsq[lev]]=core;
        cdis[lev][totsq[lev]]=0;
        totsq[lev]++;
        for (ne=V[core];ne;ne=ne->next)
        {
                if (elev[ne->id]!=lev)continue;
                tops=-1;
                b=totsq[lev];
                dfs1(ne->np,ne->val,lev,core);
                for (register int i=b;i<totsq[lev];i++)
                {
                        at.x=i;
                        at.l=a;
                        at.r=b-1;
                        if (at.l<=at.r)stacka[++topsa]=at;
                }
        }
        for (ne=V[core];ne;ne=ne->next)
        {
                if (elev[ne->id]!=lev)continue;
                solve(ne->np,lev+1);
        }
}
int root[20];
aaa heap[MAXN*50];
int toth=0;
int main()
{
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        int x,y,z;
        scanf("%d%d",&n,&m);
        for (int i=1;i<n;i++)
        {
                scanf("%d%d%d",&x,&y,&z);
                addedge(x,y,z,i);
                addedge(y,x,z,i);
        }
        memset(elev,-1,sizeof(elev));
        solve(1,0);
        for (int i=0;i<20;i++)
                if (totsq[i])
                        Build_sgt(root[i],0,totsq[i]-1,cdis[i]);

        pair<int,int> pr;
        while (~topsa)
        {
                x=cdis[stacka[topsa].lv][stacka[topsa].x];
                stacka[topsa].mx=Query_sgt(root[stacka[topsa].lv],0,totsq[stacka[topsa].lv]-1,stacka[topsa].l,stacka[topsa].r);
                stacka[topsa].mx.first+=x;
                heap[toth]=stacka[topsa--];
                push_heap(heap,heap+(++toth));
        }
        int rnow=0;
        aaa at,at2;
        while (rnow<m)
        {
                at=heap[0];
                pop_heap(heap,heap+(toth--));
                rnow++;
                printf("%d\n",at.mx.first);
                at2=at;
                at2.r=at2.mx.second-1;
                if (at2.l<=at2.r)
                {
                        x=cdis[at2.lv][at2.x];
                        at2.mx=Query_sgt(root[at2.lv],0,totsq[at2.lv]-1,at2.l,at2.r);
                        at2.mx.first+=x;
                        heap[toth]=at2;
                        push_heap(heap,heap+(++toth));
                }
                at2=at;
                at2.l=at2.mx.second+1;
                if (at2.l<=at2.r)
                {
                        x=cdis[at2.lv][at2.x];
                        at2.mx=Query_sgt(root[at2.lv],0,totsq[at2.lv]-1,at2.l,at2.r);
                        at2.mx.first+=x;
                        heap[toth]=at2;
                        push_heap(heap,heap+(++toth));
                }
        }
}
