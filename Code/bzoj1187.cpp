#include<bits/stdc++.h>
using namespace std;
int n,m,l;
struct Line{
	int d[7];
	int h(){int an=0;for(int i=l-1;i>=0;i--)an=an*3+d[i];return an;}
	int& operator[](int x){return d[x];}
	int mc(int x){
		int an=1;
		if(d[x]==1){
			for(x++;x<l;x++)if(d[x]){an=an+(d[x]==1?1:-1);if(!an)return x;}
		}else{
			for(x--;x>=0;x--)if(d[x]){an=an+(d[x]==2?1:-1);if(!an)return x;}
		}return 2333;
	}
	Line set(int x,int y){
		Line S=*this;
		S[x]=y;return S;
	}
	Line operator>>(int _){
		Line S=*this;
		for(int i=l-1;i>=1;i--)S[i]=S[i-1];
		S[0]=0;
		return S;		
	}
	Line(){memset(d,0,sizeof d);}
};
void deb(Line S){
	for(int i=0;i<l;i++)printf("%d",S.d[i]);//puts("");
}
struct hashtab{
	int sz;
	int w[2187];
	int a[2187];
	Line s[2187];
	void cl(){sz=0;memset(w,-1,sizeof w);fill(a,a+2187,INT_MIN);}
	int& operator[](Line S){
		int h=S.h();
		if(w[h]==-1)w[h]=sz,s[sz]=S,sz++;
		return a[w[h]];
	}
}f[2];
bool check(Line S){
	int cn1=0,cn2=0;
	for(int i=0;i<l;i++)cn1+=S[i]==1,cn2+=S[i]==2;
	return cn1==1&&cn2==1;
}
void up(int &x,int y){x=y>x?y:x;}
int w[101][7];
int main(){
	freopen("bzoj1187.in","r",stdin);
	scanf("%d%d",&n,&m);l=m+1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&w[i][j]);
	int cur=0;f[cur].cl();f[cur][Line()]=0;
	int ans=INT_MIN;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cur^=1;f[cur].cl();
			for(int k=0;k<f[!cur].sz;k++){
				Line S=f[!cur].s[k];int we=f[!cur][S];
//				cout<<i<<" "<<j<<" ";deb(S);cout<<" "<<we<<endl;
				int d1=S[j-1],d2=S[j];	
				if(d1==0&&d2==0){
					up(f[cur][S],we);
					if(i!=n&&j!=m)up(f[cur][S.set(j-1,1).set(j,2)],we+w[i][j]);
				}else
				if(d1==0||d2==0){
					if(i!=n)up(f[cur][S.set(j-1,d1+d2).set(j,0)],we+w[i][j]);
					if(j!=m)up(f[cur][S.set(j-1,0).set(j,d1+d2)],we+w[i][j]);
				}else
				if(d1==1&&d2==2){
					if(check(S))ans=max(ans,we+w[i][j]);
				}else 
				if(d1==2&&d2==1){
					up(f[cur][S.set(j-1,0).set(j,0)],we+w[i][j]);
				}else
				if((d1==1&&d2==1)||(d1==2&&d2==2)){
					int m1=S.mc(j),m2=S.mc(j-1);
					up(f[cur][S.set(j-1,0).set(j,0).set(m1,1).set(m2,2)],we+w[i][j]);
				}
			}
		}
		cur^=1;f[cur].cl();
		for(int k=0;k<f[!cur].sz;k++){
			Line S=f[!cur].s[k];int we=f[!cur][S];
//			cout<<i+1<<" "<<0<<" ";deb(S);cout<<" "<<we<<endl;
			up(f[cur][S>>1],we);
		}
	}cout<<ans<<endl;
	return 0;
}
