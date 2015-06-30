#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define N 1200005
#define inf 1000000000
using namespace std;
int mask;
char s[3000005];
string chars;
void gets(int mask)
{
    scanf("%s",s);
    chars=s;
    for (int j=0;j<chars.length();j++) 
	{
        mask=(mask*131+j)%chars.length();
        char t=chars[j];
        chars[j]=chars[mask];
        chars[mask]=t;
    }
}
struct lct
{
	int top;
	int fa[N],c[N][2],w[N],tag[N],q[N];
	bool rev[N];
	void add(int x,int y){
		if(x)
		{
			w[x]+=y;tag[x]+=y;
		}
	}
    void pushdown(int x){
		int l=c[x][0],r=c[x][1];
		if(tag[x])
		{
			add(l,tag[x]);add(r,tag[x]);
			tag[x]=0;
		}
	}
	bool isroot(int x){
		return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],l,r;
		if(c[y][0]==x)l=0;else l=1;r=l^1;
		if(!isroot(y))
		{
			if(c[z][0]==y)c[z][0]=x;
			else c[z][1]=x;
		}
		fa[c[x][r]]=y;fa[y]=x;fa[x]=z;
		c[y][l]=c[x][r];c[x][r]=y;
	}
	void splay(int x){
		top=0;q[++top]=x;
		for(int i=x;!isroot(i);i=fa[i])
			q[++top]=fa[i];
		for(int i=top;i;i--)
			pushdown(q[i]);
		while(!isroot(x))
		{
			int y=fa[x],z=fa[y];
			if(!isroot(y))
			{
				if(c[y][0]==x^c[z][0]==y)rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
	}
	void access(int x){
		for(int t=0;x;t=x,x=fa[x])
			splay(x),c[x][1]=t;
	}
	void link(int x,int f){
		fa[x]=f;access(f);splay(f);add(f,w[x]);
	}
	void cut(int x){
		access(x);splay(x);add(c[x][0],-w[x]);
		fa[c[x][0]]=0;c[x][0]=0;
	}		
}t;
struct sam
{
	int l[N],fa[N],to[N][26];
	int cnt,last;
	int p,np,q,nq;
	sam(){
		last=++cnt;
	}
	void extend(int c){
		p=last;last=np=++cnt;t.w[np]=1;l[np]=l[p]+1;
		for(;p&&!to[p][c];p=fa[p])to[p][c]=np;
		if(!p)fa[np]=1,t.link(np,1);
		else
		{
			q=to[p][c];
			if(l[p]+1==l[q])fa[np]=q,t.link(np,q);
			else
			{
				nq=++cnt;l[nq]=l[p]+1;
				memcpy(to[nq],to[q],sizeof(to[q]));
				fa[nq]=fa[q];
				t.link(nq,fa[q]);
				fa[np]=fa[q]=nq;
				t.cut(q);t.link(q,nq);t.link(np,nq);
				for(;to[p][c]==q;p=fa[p])to[p][c]=nq;
			}
		}
	}
	void build(){
		scanf("%s",s);
		int l=strlen(s);
		for(int i=0;i<l;i++)
			extend(s[i]-'A');
	}
	void add(){
		gets(mask);
		int l=chars.length();
		for(int i=0;i<l;i++)
			extend(chars[i]-'A');
	}
	int query(){
		gets(mask);
		int p=1,l=chars.length();
		for(int i=0;i<l;i++)
			if(!(p=to[p][chars[i]-'A']))return 0;
		t.splay(p);
		return t.w[p];
	}
}sam;
int main()
{
	freopen("bzoj2555.in","r",stdin);
	int Q;scanf("%d",&Q);
	sam.build();
	while(Q--)
	{
		scanf("%s",s);
		if(s[0]=='A')sam.add();
		else 
		{
			int ans=sam.query();
			printf("%d\n",ans);
			mask^=ans;
		}
	}
	return 0;
}
