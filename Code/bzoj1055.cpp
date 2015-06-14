#include<bits/stdc++.h>
using namespace std;
int mp[128];
char rmp[5]="WING";
int K[4];
int A[4][16][2];
short f[200][200][4];
short vis[200][200][4];
char s[200];
short dp(int l,int r,int x){
	if(l==r)return mp[s[l]]==x;
	if(vis[l][r][x])return f[l][r][x];
	vis[l][r][x]=1;
	for(int i=l;i<r;i++)
	for(int j=0;j<K[x];j++){
		if(dp(l,i,A[x][j][0])&&dp(i+1,r,A[x][j][1]))
			return f[l][r][x]=1;
	}return f[l][r][x]=0;
}
int main(){
	for(int i=0;i<4;i++)cin>>K[i];
	mp['W']=0;mp['I']=1;mp['N']=2;mp['G']=3;
	for(int i=0;i<4;i++)
	for(int j=0;j<K[i];j++){
		char s[2];scanf("%s",s);
		A[i][j][0]=mp[s[0]];
		A[i][j][1]=mp[s[1]];
	}scanf("%s",s);
	int len=strlen(s);
	string anss;
	for(int i=0;i<4;i++)
		if(dp(0,len-1,i))
		anss.push_back(rmp[i]);
	if(!anss.size())puts("The name is wrong!");
	else cout<<anss<<endl;
	return 0;
}
