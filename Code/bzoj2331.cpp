#include<bits/stdc++.h>
using namespace std;
const int mo=20110520;
int mp[101][101];
int l;
struct L{
	int d[11];
	int& operator[](int x){return d[x];}
	L s(int x,int y){
		L S=*this;S[x]=y;return S;
	}
	L operator>>(int _){
		L S=*this;
		for(int i=l-1;i>=1;i--)S[i]=S[i-1];S[0]=0;return S;
	}
	int h(){
		int an=0;
		for(int i=l-1;i>=0;i--)an=an*3+d[i];return an;
	}
};
struct hashtab{
	int sz;
	int tab[177147];
	int w[177147];
	L s[177147];
	hashtab(){sz=0;memset(tab,-1,sizeof tab);}
	void cl(){
		for(int i=0;i<sz;i++)tab[s[i].h()]=-1;
		sz=0;
	}
	int& operator[](L S){
		int h=S.h();
		if(tab[h]==-1)tab[h]=sz,w[sz]=0,s[sz]=S,sz++;
		return w[tab[h]];
	}
}f[2];
void up(int &x,int y){x+=y;if(x>=mo)x-=mo;}
int n,m;
void deb(int x,int y,L S,int w){
	fprintf(stderr,"%d %d ",x,y);
	for(int i=0;i<l;i++)fprintf(stderr,"%d",S[i]);
	fprintf(stderr," %d\n",w);
}
int main(){
	freopen("bzoj2331.in","r",stdin);
	scanf("%d%d",&n,&m);
	char c=' ';
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		while(c!='*'&&c!='_')c=getchar();
		if(n>=m)
			mp[i][j]=c=='*';
		else mp[j][i]=c=='*';
		c=getchar();
	}
	if(n<m)swap(n,m);l=m+1;
	int cur=0;f[cur][L()]=1;
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cur^=1;f[cur].cl();
			for(int k=0;k<f[!cur].sz;k++){
				L S=f[!cur].s[k];int w=f[!cur][S];
//				deb(i,j,S,w);
				int d1=S[j-1],d2=S[j];
				if(mp[i][j]){
					if(d1==0&&d2==0)
					up(f[cur][S],w);
					continue;
				}
				if(d1==0&&d2==0){
					if(i!=n&&j!=m)up(f[cur][S.s(j-1,2).s(j,2)],w);
					if(i!=n)up(f[cur][S.s(j-1,1).s(j,0)],w);
					if(j!=m)up(f[cur][S.s(j-1,0).s(j,1)],w);
				}else
				if(d1==1&&d2==1){
					up(f[cur][S.s(j-1,0).s(j,0)],w);
				}else
				if(d1==0&&d2==1){
					if(i!=n)up(f[cur][S.s(j-1,1).s(j,0)],w);
					if(j!=m)up(f[cur][S.s(j-1,0).s(j,2)],w);
				}else
				if(d1==0&&d2==2){
					if(i!=n)up(f[cur][S.s(j-1,2).s(j,0)],w);
					up(f[cur][S.s(j-1,0).s(j,0)],w);					
				}else
				if(d1==1&&d2==0){
					if(j!=m)up(f[cur][S.s(j-1,0).s(j,1)],w);
					if(i!=n)up(f[cur][S.s(j-1,2).s(j,0)],w);					
				}else
				if(d1==2&&d2==0){
					if(j!=m)up(f[cur][S.s(j-1,0).s(j,2)],w);
					up(f[cur][S.s(j-1,0).s(j,0)],w);					
				}	
			}
		}
		cur^=1;f[cur].cl();
		for(int k=0;k<f[!cur].sz;k++){
			L S=f[!cur].s[k];int w=f[!cur][S];
//			deb(i+1,0,S,w);
			f[cur][S>>1]=w;
		}
	}for(int i=0;i<f[cur].sz;i++)
		ans=(ans+f[cur].w[i])%mo;
	cout<<ans<<endl;
	return 0;
}
