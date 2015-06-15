#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
 
#define Maxn 200010
#define l(x) ch[x][0]
#define r(x) ch[x][1]
#define lc(x) c[x][0]
#define rc(x) c[x][1]
 
using namespace std;
 
int n,m,tot=0,_tot=0,tree[Maxn]={0};
int a[Maxn],last[Maxn],pos[Maxn],next[Maxn],N,rank[Maxn];
int maxt[40000005],ch[40000010][2];
int c[2000010][2],root[2000010];

stack<int> _mL,mL;

int get(){
	if(mL.empty()) return ++tot;
	int tp=mL.top();
	mL.pop();
	return tp;
}

int _get(){
	if(_mL.empty()) return ++_tot;
	int tp=_mL.top();
	_mL.pop();
	return tp;
}

int _change(int o,int l,int r,int qx,int qv){
    int x=++_tot; maxt[x]=max(maxt[o],qv);
    l(x)=l(o); r(x)=r(o);
    if(l==r) return x;
    int mid=(l+r)>>1;
    if(qx<=mid) l(x)=_change(l(x),l,mid,qx,qv);
    else r(x)=_change(r(x),mid+1,r,qx,qv);
    return x;
}

int _query(int o,int l,int r,int ql,int qr){
	if(!o) return 0;
    if(ql<=l&&r<=qr) return maxt[o];
    int mid=(l+r)>>1,res=0;
    if(ql<=mid) res=max(res,_query(l(o),l,mid,ql,qr));
    if(mid<qr) res=max(res,_query(r(o),mid+1,r,ql,qr));
    return res;
}

int query(int o,int l,int r,int ql,int qr,int qa,int qb){
    if(ql<=l&&r<=qr) return _query(root[o],1,n,qa,qb);
    int mid=(l+r)>>1,res=0;
    if(ql<=mid) res=max(res,query(lc(o),l,mid,ql,qr,qa,qb));
    if(mid<qr) res=max(res,query(rc(o),mid+1,r,ql,qr,qa,qb));
    return res;
}

int change(int o,int l,int r,int qx,int qy,int qv){
    int x=++tot;
    lc(x)=lc(o); rc(x)=rc(o);
    root[x]=_change(root[o],1,n,qy,qv);
    if(l==r) return x;
    int mid=(l+r)>>1;
    if(qx<=mid) lc(x)=change(lc(o),l,mid,qx,qy,qv);
    else rc(x)=change(rc(o),mid+1,r,qx,qy,qv);
    return x;
}

bool cmp(const int &a,const int &b){
    return last[a]<last[b];
}

int main(){
	freopen("bzoj3489.in","r",stdin);
    scanf("%d%d",&n,&m);
    memset(last,0,sizeof(last));
    for(int i=1;i<=n;i++) pos[i]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        last[i]=pos[a[i]],pos[a[i]]=i;
    }
    memset(next,0,sizeof(next));
    for(int i=1;i<=n;i++) pos[i]=n+1;
    for(int i=n;i>=1;i--){
        rank[i]=i;
        next[i]=pos[a[i]],pos[a[i]]=i;
    }
    sort(rank+1,rank+n+1,cmp);
    int j=1,ans=0,l,r;
    for(int i=0;i<n;i++){
        if(i) tree[i]=tree[i-1];
        while(j<=n&&last[rank[j]]==i){
            tree[i]=change(tree[i],0,n+1,next[rank[j]],rank[j],a[rank[j]]);
            j++;
        }
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&l,&r);
        l=(l+ans)%n+1;
        r=(r+ans)%n+1;
        if(l>r) swap(l,r);
        ans=query(tree[l-1],0,n+1,r+1,n+1,l,r);
        printf("%d\n",ans);
    }
    return 0;
}
