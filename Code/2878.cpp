#include<cstdio>
#define N 100010
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
int n,m,i,j,x,y,z;
int g[N],nxt[N<<1],w[N<<1],v[N<<1],ed,pre[N],ch[N],d[N],fw[N],st,sum;
int cnt,a[N<<1],s[N<<1];
double up[N],down[N],ans,p;
bool vis[N],in[N];
inline void add(int x,int y,int z){d[x]++;v[++ed]=y;w[ed]=z;nxt[ed]=g[x];g[x]=ed;}
void dfs1(int x,int f){
  for(int i=g[x];i;i=nxt[i])if(v[i]!=f&&!in[v[i]])dfs1(v[i],x),ch[x]++,down[x]+=down[v[i]]+w[i];
  if(ch[x])down[x]/=ch[x];
}
void dfs2(int x,int f){
  for(int i=g[x];i;i=nxt[i])if(v[i]!=f&&!in[v[i]]){
    up[v[i]]=w[i];
    if(d[x]>1)up[v[i]]+=(up[x]*(d[x]-ch[x])+down[x]*ch[x]-w[i]-down[v[i]])/(d[x]-1);
    dfs2(v[i],x);
  }
}
void find(int x,int f,int l){
  if(st)return;
  pre[x]=f;fw[x]=l;
  if(vis[x]){st=f;return;}
  vis[x]=1;
  for(int i=g[x];i;i=nxt[i])if(v[i]!=f)find(v[i],x,w[i]);
}
int main(){
  for(read(n),read(m);i<m;i++)read(x),read(y),read(z),add(x,y,z),add(y,x,z);
  if(m<n)dfs1(1,0),dfs2(1,0);else{
    find(1,0,0);
    for(in[a[cnt=1]=st]=1,i=pre[st];i!=st;i=pre[i])in[a[++cnt]=i]=1;
    for(i=1;i<=cnt;i++)a[i+cnt]=a[i],s[i+1]=s[i+cnt+1]=fw[a[i]];
    for(i=1;i<=cnt;i++)dfs1(a[i],0);
    for(i=1;i<=cnt;i++){
      //i->j
      j=i+1;p=0.5;sum=s[j];
      up[a[i]]+=p*(sum+down[a[j]])*ch[a[j]]/(ch[a[j]]+1);
      p/=ch[a[j]]+1;
      for(j=i+2;j<i+cnt-1;j++){
        sum+=s[j];
        up[a[i]]+=p*(sum+down[a[j]])*ch[a[j]]/(ch[a[j]]+1);
        p/=ch[a[j]]+1;
      }
      j=i+cnt-1;
      sum+=s[j];
      up[a[i]]+=p*(sum+down[a[j]]);
      //j<-i
      j=i+cnt-1;p=0.5;sum=s[j+1];
      up[a[i]]+=p*(sum+down[a[j]])*ch[a[j]]/(ch[a[j]]+1);
      p/=ch[a[j]]+1;
      for(j=i+cnt-2;j>i+1;j--){
        sum+=s[j+1];
        up[a[i]]+=p*(sum+down[a[j]])*ch[a[j]]/(ch[a[j]]+1);
        p/=ch[a[j]]+1;
      }
      j=i+1;
      sum+=s[j+1];
      up[a[i]]+=p*(sum+down[a[j]]);
    }
    for(i=1;i<=cnt;i++)dfs2(a[i],0);
  }
  for(i=1;i<=n;i++)ans+=(down[i]*ch[i]+up[i]*(d[i]-ch[i]))/d[i];
  printf("%.5f",ans/n);
  return 0;
}
