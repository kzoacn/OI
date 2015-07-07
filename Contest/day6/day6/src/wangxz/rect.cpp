#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MOD(10007);
const int N(1501);
struct hh{
	int h,sz;
}s[N];
int n,top,lm[N][N],rm[N][N],lu[N][N],ru[N][N],ld[N][N],rd[N][N],rdh[N],rdl[N],luh[N],lul[N];
bool mp[N][N];
char str[N];
inline bool get(){
	char c=0;
	for(;c!='C'&&c!='B';c=getchar());
	return c=='C';
}
inline int check(int x){
	if(x>=MOD)x%=MOD;
	if(x<0)x=(x%MOD+MOD)%MOD;
	return x;
}
inline int sum(int s[N][N],int x1,int y1,int x2,int y2){
	if(x1>x2||y1>y2)return 0;
//	x1=max(x1,0);y1=max(y1,0);
	return check(s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1]);
}
int main(){
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
	scanf("%d",&n);
	for(int i(1);i<=n;i++){
		scanf("%s",str+1);
		for(int j(1);j<=n;j++)
			mp[i][j]=str[j]=='C'?1:0;
	}
	for(int i(1);i<=n;i++){
		for(int j(1);j<=n;j++)
			lm[i][j]=mp[i][j]?lm[i][j-1]+1:0;
		for(int j(n);j>=1;j--)
			rm[i][j]=mp[i][j]?rm[i][j+1]+1:0;
	}
	//lu
	for(int j(1);j<=n;j++){
		int top=0,ans=0;
		for(int i(n);i>=1;i--){
			int t=0;
			while(top&&s[top].h>=rm[i][j])t+=s[top].sz,ans=check(ans-s[top].h*s[top].sz),top--;
			s[++top].h=rm[i][j];s[top].sz=t+1;
			ans=check(ans+rm[i][j]*s[top].sz);
			lu[i][j]=check(ans-mp[i][j]);
		}
	}
	//ru
	for(int j(1);j<=n;j++){
		int top=0,ans=0;
		for(int i(n);i>=1;i--){
			int t=0;
			while(top&&s[top].h>=lm[i][j])t+=s[top].sz,ans=check(ans-s[top].h*s[top].sz),top--;
			s[++top].h=lm[i][j];s[top].sz=t+1;
			ans=check(ans+lm[i][j]*s[top].sz);
			ru[i][j]=check(ans-mp[i][j]);
		}
	}
	//ld
	for(int j(1);j<=n;j++){
		int top=0,ans=0;
		for(int i(1);i<=n;i++){
			int t=0;
			while(top&&s[top].h>=rm[i][j])t+=s[top].sz,ans=check(ans-s[top].h*s[top].sz),top--;
			s[++top].h=rm[i][j];s[top].sz=t+1;
			ans=check(ans+rm[i][j]*s[top].sz);
			ld[i][j]=check(ans-mp[i][j]);
		}
	}
	//rd
	for(int j(1);j<=n;j++){
		int top=0,ans=0;
		for(int i(1);i<=n;i++){
			int t=0;
			while(top&&s[top].h>=lm[i][j])t+=s[top].sz,ans=check(ans-s[top].h*s[top].sz),top--;
			s[++top].h=lm[i][j];s[top].sz=t+1;
			ans=check(ans+lm[i][j]*s[top].sz);
			rd[i][j]=check(ans-mp[i][j]);
		}
	}
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			if(mp[i][j]){
				rdh[i]=check(rdh[i]+rd[i][j]);
				rdl[j]=check(rdl[j]+rd[i][j]);
				luh[i]=check(luh[i]+lu[i][j]);
				lul[j]=check(lul[j]+lu[i][j]);
			}
	for(int i(n);i>=1;i--)
		luh[i]=check(luh[i]+luh[i+1]),lul[i]=check(lul[i]+lul[i+1]);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			rd[i][j]=check(rd[i][j]+rd[i-1][j]+rd[i][j-1]-rd[i-1][j-1]);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			ld[i][j]=check(ld[i][j]+ld[i-1][j]+ld[i][j-1]-ld[i-1][j-1]);
	int ans=0;
	for(int i(1);i<=n;i++)
		ans=check(ans+rdh[i]*luh[i+1]);
	for(int i(1);i<=n;i++)
		ans=check(ans+rdl[i]*lul[i+1]);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			if(mp[i][j]){
				ans=check(ans-lu[i][j]*sum(rd,1,1,i-1,j-1)%MOD);
				ans=check(ans-ru[i][j]*sum(ld,1,j+1,i-1,n)%MOD);
			}
	printf("%d\n",ans);
	return 0;
}
