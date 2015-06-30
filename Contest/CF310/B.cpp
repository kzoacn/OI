#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long LL;
struct seg{
    LL l,r,id;
    bool operator<(const seg &o)const{
        return r!=o.r?r<o.r:l<o.l;
    }
}se[maxn],s[maxn];
LL n,m;
bool bycmp(seg a,seg b){
    return a.id<b.id;
}
bool by(pair<LL,LL> a,pair<LL,LL> b){
    return a.second<b.second;
}
set<pair<LL,int> >S;
int main(){
    scanf("%I64d%I64d",&n,&m);
    for(LL i=1;i<=n;i++)
        scanf("%I64d%I64d",&s[i].l,&s[i].r);
    for(LL i=1;i<=m;i++){
        LL x;scanf("%I64d",&x);
        S.insert(make_pair(x,i));
    }
    for(LL i=1;i<n;i++){
        se[i].l=s[i+1].l-s[i].r;
        se[i].r=s[i+1].r-s[i].l;
        se[i].id=i;
    }sort(se+1,se+n);
    //sort(a+1,a+1+m);
    static LL anss[maxn];
    for(int i=1;i<n;i++){
        set<pair<LL,int> >::iterator it=S.lower_bound(make_pair(se[i].l,-1));
        if(it==S.end()||it->first>se[i].r){
            return puts("No"),0;
        }else{
            anss[se[i].id]=it->second;
            S.erase(it);
        }
    }
    puts("Yes");
    for(LL i=1;i<n;i++)
        printf("%I64d%c",anss[i]," \n"[i==n-1]);
    return 0;
}
