#include<cstdio>
#include<cstring>
#define N 1<<20
int n,T,k,tot=1,S=1,las=1,fail[N],ch[N][26],val[N],f[N],len[N],id[N],c[N],i,j,l;
char s[N],op[N],*O=op;
void add(char c){
    int p=las,np=++tot;
    for(val[np]=1,len[np]=len[p]+1;p&&!ch[p][c];p=fail[p])ch[p][c]=np;
    if(las=np,!p)fail[np]=S;
    else if(len[p]+1==len[ch[p][c]])fail[np]=ch[p][c];
    else{
        int q=ch[p][c],r=++tot;len[r]=len[p]+1;if(!T)val[r]=1;
        fail[r]=fail[q],memcpy(ch[r],ch[q],sizeof(ch[q]));
        for(fail[np]=fail[q]=r;p&&ch[p][c]==q;p=fail[p])ch[p][c]=r;
    }
}
int main(){
    scanf("%s",s+1);scanf("%d%d",&T,&k);
    for(n=1;s[n];n++)add(s[n]-'a');n--;
    for(i=1;i<=tot;i++)c[len[i]]++;
    for(i=1;i<=n;i++)c[i]+=c[i-1];
    for(i=tot;i;i--)id[c[len[i]]--]=i;
    if(T)for(j=tot;j;j--)i=id[j],val[fail[i]]+=val[i];
    for(val[1]=0,j=tot;j;j--)
    for(i=id[j],f[i]=val[i],l=0;l<26;l++)f[i]+=f[ch[i][l]];
    if(f[1]<k)return puts("-1"),0;
    for(i=S;k>val[i];){
        for(k-=val[i],j=0;j<26;j++)
        if(f[ch[i][j]]<k)k-=f[ch[i][j]];
        else{*O++=j+'a';i=ch[i][j];break;}
    }
    puts(op);
}
