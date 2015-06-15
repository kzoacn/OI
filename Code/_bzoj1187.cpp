#include<cstdio>
#include<cstring>
#include<cctype>
#include<climits>
#include<iostream>
#include<algorithm>
using namespace std;
 
int l;
struct Line{
    int d[7];
    Line(){memset(d,0,sizeof d);}
    inline int hash(){
        int re=0,mi=1;for(int i=0;i<l;++i,mi*=3)re+=d[i]*mi;return re;
    }
    inline void flush(){
        for(int i=l-1;i>=1;--i)d[i]=d[i-1];d[0]=0;
    }
    inline int getleftins(int x){
        int sav=0;
        for(int i=x;i>=0;--i){
            if(d[i]==2)++sav;else if(d[i]==1)--sav;
            if(sav==0)return i;
        }
    }
    inline int getrightins(int x){
        int sav=0;
        for(int i=x;i<l;++i){
            if(d[i]==1)++sav;else if(d[i]==2)--sav;
            if(sav==0)return i;
        }
    }
    Line change(int ins,int x){
        Line re=*this;re.d[ins]=x;return re;
    }
    inline int getlnum(){
        int re=0;for(int i=0;i<l;++i)re+=d[i]==1;return re;
    }
    inline int getrnum(){
        int re=0;for(int i=0;i<l;++i)re+=d[i]==2;return re;
    }
};
struct Hashset{
    int ins[2187],w[2187],ind;
    Line s[2187];
    inline void reset(){ind=0,memset(ins,-1,sizeof ins);}
    inline void insert(Line l,int _w){
        int hash=l.hash();
        if(ins[hash]==-1)ins[hash]=ind,w[ind]=_w,s[ind++]=l;
        else w[ins[hash]]=max(w[ins[hash]],_w);
    }
}S[2];
 
#define N 110
#define M 10
int w[N][M];
 
int main(){
	freopen("bzoj1187.in","r",stdin);
    int n,m;scanf("%d%d",&n,&m);register int i,j,k;l=m+1;
    for(i=1;i<=n;++i)for(j=1;j<=m;++j)scanf("%d",&w[i][j]);
     
    int now=0,last=1;
    Line begin;S[now].reset(),S[now].insert(begin,0);
     
    int res=-1<<30;
    Line nowst;int nowf,d1,d2,ins1,ins2;
    for(i=1;i<=n;++i){
        for(j=1;j<=m;++j){
            swap(now,last),S[now].reset();
            for(k=0;k<S[last].ind;++k){
                nowst=S[last].s[k];nowf=S[last].w[k];
                d1=nowst.d[j-1],d2=nowst.d[j];
                if(d1==0&&d2==0){
                    S[now].insert(nowst,nowf);
                    if(i!=n&&j!=m)S[now].insert(nowst.change(j-1,1).change(j,2),nowf+w[i][j]);
                }
                else if(d1==0||d2==0){
                    if(i!=n)S[now].insert(nowst.change(j-1,d1+d2).change(j,0),nowf+w[i][j]);
                    if(j!=m)S[now].insert(nowst.change(j-1,0).change(j,d1+d2),nowf+w[i][j]);
                }
                else if(d1==1&&d2==1){
                    ins1=nowst.getrightins(j),ins2=nowst.getrightins(j-1);
                    S[now].insert(nowst.change(j-1,0).change(j,0).change(ins1,1).change(ins2,2),nowf+w[i][j]);
                }
                else if(d1==1&&d2==2){
                    if(nowst.getlnum()==1&&nowst.getrnum()==1)res=max(res,nowf+w[i][j]);
                }
                else if(d1==2&&d2==1){
                    S[now].insert(nowst.change(j-1,0).change(j,0),nowf+w[i][j]);
                }
                else if(d1==2&&d2==2){
                    ins1=nowst.getleftins(j),ins2=nowst.getleftins(j-1);
                    S[now].insert(nowst.change(j-1,0).change(j,0).change(ins1,1).change(ins2,2),nowf+w[i][j]);
                }
            }
        }
        swap(now,last),S[now].reset();
        for(k=0;k<S[last].ind;++k){
            nowst=S[last].s[k],nowf=S[last].w[k];
            nowst.flush();
            S[now].insert(nowst,nowf);
        }
    }
     
    printf("%d\n",res);
     
    return 0;
}
        
