#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
LL mo=1e9;
LL A[101][101];
LL Gauss(int n){
	n--;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)A[i][j]%=mo;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)A[i][j]=(A[i][j]+mo)%mo;
	LL ans=n%2?mo-1:1;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			while(A[j][i]){
				LL t=A[i][i]/A[j][i];
				for(int k=0;k<n;k++)
				A[i][k]=(A[i][k]-A[j][k]*t%mo+mo)%mo;
				swap(A[i],A[j]);
				ans=mo-ans;
			}
		}ans=ans*A[i][i]%mo;
	}return (ans%mo+mo)%mo;
}
int mp[10][10],tot;
int a[10][10];
void add(int x,int y){
	A[x][y]++;
}
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
void make(){
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)if(!a[i][j])
	mp[i][j]=tot++;
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++){
		if(!a[i][j])
		for(int k=0;k<4;k++){
			int x=dx[k]+i,y=dy[k]+j;
			if(x<0||x>=n||y<0||y>=m)continue;
			if(!a[x][y]){
				add(mp[i][j],mp[x][y]);
			}
		}
	}for(int i=0;i<tot;i++)A[i][i]=-accumulate(A[i],A[i]+tot,0);
}
char s[10];
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>s;
		for(int j=0;j<m;j++)
			a[i][j]=s[j]=='*';
	}
	make();
	cout<<Gauss(tot)<<endl;
	return 0;
}
