#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+205;
int pos[maxn],son[maxn<<1][27],pre[maxn<<1],val[maxn<<1],f[maxn<<1],sum[maxn<<1],b[maxn<<1];    
int last,tot,n,m;
char s[maxn];
int pushback(int x){
    val[++tot]=x;
    return tot;
}
void push(int x){
    int p=last;
    int np=pushback(val[p]+1);
    for(;p!=-1&&!son[p][x];p=pre[p])son[p][x]=np;
    if(p==-1)pre[np]=0;
    else{
        int q=son[p][x];
        if(val[q]==val[p]+1)pre[np]=q;
        else{
            int nq=pushback(val[p]+1);
            memcpy(son[nq],son[q],sizeof(son[q]));
            pre[nq]=pre[q];
            pre[q]=pre[np]=nq;
            for(;p!=-1&&son[p][x]==q;p=pre[p])son[p][x]=nq;
        }
    }last=np;
}
pair<int,int>v[maxn<<1];
int main(){
    pre[0]=-1;
    scanf("%d",&n);s[0]='0';
    for(int i=1;i<=n;i++){
        char c=getchar();while(!isalpha(c))c=getchar();
        while(isalpha(c))s[++m]=c,c=getchar();
        pos[i]=m;
        s[++m]='z'+1;
    }m--;
    for(int i=1;i<=m;i++)push(s[i]-'a');
 
    for(int i=1;i<=tot;i++)v[i].first=val[i],v[i].second=i;
    sort(v+1,v+1+tot);
    int p=0;
    for(int i=1;i<=m;i++)p=son[p][s[i]-'a'],f[p]=1;
    for(int i=tot;i;i--)f[pre[v[i].second]]+=f[v[i].second];
     
    int i=1;pos[0]=-1;
    for(int i=1;i<=n;i++){
        int p=0;
        for(int j=pos[i-1]+2;j<=pos[i];j++) 
        p=son[p][s[j]-'a'];
        printf("%d\n",f[p]);
    }
    return 0;
}
