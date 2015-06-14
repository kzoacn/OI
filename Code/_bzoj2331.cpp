#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<algorithm>
using namespace std;
  
#define R 110
#define C 110
int r,c;
bool Read[R][C],map[R][C];
  
char s[C];
  
static const int mod=20110520;
  
inline void inc(int&x,int y){if((x+=y)>=mod)x-=mod;}
  
struct State{
    int d[11];
    State(){memset(d,0,sizeof d);}
  
    inline int hash(){
        int re=0,mi=1;
        for(int i=0;i<=c;++i)re+=mi*d[i],mi*=3;
        return re;
    }
    inline int get(int ins){return d[ins];}
    inline State change(int ins,int x){State re=*this;re.d[ins]=x;return re;}
    inline void flush(){
        for(int i=c;i>=1;--i)d[i]=d[i-1];d[0]=0;
    }
      
    inline void print(){for(int i=0;i<=c;++i)printf("%d",d[i]);}
};
  
struct HashSet{
    int ins[200010],w[200010],ind;State S[200010];
  
    inline void reset(){memset(ins,-1,sizeof ins),ind=0;}
  
    inline void Insert(State s,int _w){
        //s.print(),printf(" %d\n",_w);
        int hash=s.hash();
        if(ins[hash]==-1)S[ind]=s,w[ind]=_w,ins[hash]=ind++;else inc(w[ins[hash]],_w);
    }
}set[2];
 
void deb(int x,int y,State S,int w){
	printf("%d %d ",x,y);
	for(int i=0;i<c+1;i++)printf("%d",S.d[i]);
	printf(" %d\n",w);
} 
int main(){
	freopen("bzoj2331.in","r",stdin);
    scanf("%d%d",&r,&c);register int i,j,k;
    for(i=1;i<=r;++i){
        scanf("%s",s+1);
        for(j=1;j<=c;++j)Read[i][j]=s[j]!='*';
    }
    if(r<c){for(i=1;i<=r;++i)for(j=1;j<=c;++j)map[j][i]=Read[i][j];swap(r,c);}
    else for(i=1;i<=r;++i)for(j=1;j<=c;++j)map[i][j]=Read[i][j];
  
    int now=0,last=1;
  
    State begin;set[now].reset(),set[now].Insert(begin,1);
  
    State nows;int noww,d1,d2;
    for(i=1;i<=r;++i){
        for(j=1;j<=c;++j){
            swap(now,last),set[now].reset();
  
            for(k=0;k<set[last].ind;++k){
                nows=set[last].S[k],noww=set[last].w[k],d1=nows.get(j-1),d2=nows.get(j);
//  				deb(i,j,nows,noww);
                if(!map[i][j]){
                    if(d1==0&&d2==0)set[now].Insert(nows,noww);
                }
                else{
                    if(d1==0&&d2==0){
                        if(i!=r&&j!=c)set[now].Insert(nows.change(j-1,2).change(j,2),noww);
                        if(i!=r)set[now].Insert(nows.change(j-1,1).change(j,0),noww);
                        if(j!=c)set[now].Insert(nows.change(j-1,0).change(j,1),noww);
                    }
                    if(d1==1&&d2==0){
                        if(j!=c)set[now].Insert(nows.change(j-1,0).change(j,1),noww);
                        if(i!=r)set[now].Insert(nows.change(j-1,2).change(j,0),noww);
                    }
                    if(d1==0&&d2==1){
                        if(i!=r)set[now].Insert(nows.change(j-1,1).change(j,0),noww);
                        if(j!=c)set[now].Insert(nows.change(j-1,0).change(j,2),noww);
                    }
                    if(d1==2&&d2==0){
                        if(j!=c)set[now].Insert(nows.change(j-1,0).change(j,2),noww);
                        set[now].Insert(nows.change(j-1,0).change(j,0),noww);
                    }
                    if(d1==0&&d2==2){
                        if(i!=r)set[now].Insert(nows.change(j-1,2).change(j,0),noww);
                        set[now].Insert(nows.change(j-1,0).change(j,0),noww);
                    }
                    if(d1==1&&d2==1)set[now].Insert(nows.change(j-1,0).change(j,0),noww);
                }
            }
        }
  
        swap(now,last),set[now].reset();
        for(k=0;k<set[last].ind;++k){
            nows=set[last].S[k],noww=set[last].w[k],nows.flush();
//           deb(i+1,0,nows,noww);
            set[now].Insert(nows,noww);
        }
  
    }
  
    int res=0;for(k=0;k<set[now].ind;++k)inc(res,set[now].w[k]);
  
    printf("%d\n",res);
  
    return 0;
}
