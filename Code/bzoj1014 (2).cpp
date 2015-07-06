#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int m,len;
char s[100000]; 
unsigned long long mi[200000];
struct treap_node{
    treap_node *left,*right;
    int fix,size;
    unsigned int hashz;
    char val;
    treap_node(char val=0): val(val) {left=right=NULL; fix=rand(); hashz=(int)(val)-96; size=1; }
    inline int lsize()
      {
        if (left) 
          return left->size;
        else
          return 0;
      }
    inline int rsize()
      {
        if (right)
          return right->size;
        else
          return 0; 
      }
    inline void Maintain()
      {
        size=1;
        size+=lsize()+rsize();
        hashz=(int)(val)-96; 
        if (left&&!right)
          hashz=left->hashz+hashz*mi[lsize()];
        if (!left&&right)
          hashz=hashz+right->hashz*mi[1]; 
        if (left&&right)
          hashz=left->hashz+hashz*mi[lsize()]+right->hashz*mi[lsize()+1];
      }
}pool[200000],*cur=pool;
inline treap_node* newnode(char c){
    if(cur-pool<200000)
    return *cur=treap_node(c),cur++;
    return new treap_node(c);
}
treap_node *root;
typedef pair<treap_node*,treap_node*> droot;
treap_node *merge(treap_node *a,treap_node *b)
{
    if (!a) return b; if (!b) return a;
    if (a->fix<b->fix)
      {
        a->right=merge(a->right,b);
        a->Maintain();
        return a;
      }
    else
      {
        b->left=merge(a,b->left);
        b->Maintain();
        return b;
      }
}
droot split(treap_node *x,int k)
{
    if (!x) return droot(NULL,NULL);
    droot y;
    if (k<=x->lsize())
      {
        y=split(x->left,k);
        x->left=y.second;
        x->Maintain();
        y.second=x;
      }
    else
      {
        y=split(x->right,k-x->lsize()-1);
        x->right=y.first;
        x->Maintain();
        y.first=x;
      }
    return y;
}
inline void insert(int xi,char ch)
{
    droot x;
    treap_node *temp;
    x=split(root,xi);
    temp=newnode(ch);
    x.first=merge(x.first,temp);
    root=merge(x.first,x.second);
}
inline void del(int xi,int k)
{
    droot x,y;
    x=split(root,xi-1);
    y=split(x.second,1);
    root=merge(x.first,y.second);
}
inline void work(int x,int y)
{
    int l,r,mid,ans=0;
    unsigned long long t1,t2;
    droot a,b;
    l=1; r=min(len-x+1,len-y+1);
    while (l<=r)
      {
        mid=(l+r)/2;  
        a=split(root,x-1); b=split(a.second,mid);
        b.first->Maintain();
        t1=b.first->hashz;
        a.second=merge(b.first,b.second); root=merge(a.first,a.second);
        a=split(root,y-1); b=split(a.second,mid);
        b.first->Maintain();
        t2=b.first->hashz; 
        a.second=merge(b.first,b.second); root=merge(a.first,a.second);
        if (t1==t2)
          l=mid+1,ans=mid; 
        else
          r=mid-1; 
      }
    printf("%d\n",ans);
}
inline int in(){
    int r=0,f=1;char c=getchar();
    while(!isdigit(c))f=c=='-'?-1:1,c=getchar();
    while(isdigit(c))r=r*10+c-'0',c=getchar();
    return r*f;
}
int main()
{
    int i,x,y,t=0;
    char opt,ch;
    treap_node *temp;
    scanf("%s",&s);
    len=strlen(s);
    scanf("%d",&m);
    mi[0]=1;
    for (i=1;i<=min(100000,len*2);++i)
      mi[i]=mi[i-1]*27; 
    for (i=0;i<=len-1;++i)
      {
        temp=newnode(s[i]);
        root=merge(root,temp);
      }
    for (i=1;i<=m;++i)
      {
        opt=getchar();
        while (opt!='Q'&&opt!='R'&&opt!='I')
          opt=getchar();
        if (opt=='Q')
          {
            x=in();y=in();
            work(x,y);
          }
        if (opt=='I')
          {
            x=in();
            ch=getchar();
            while (ch<'a'||ch>'z')
              ch=getchar();
            insert(x,ch);
            len++;
          }     
        if (opt=='R')
          {
            x=in();
            ch=getchar();
            while (ch<'a'||ch>'z')
              ch=getchar();
            del(x,1);
            insert(x-1,ch);
          }
      }
}
