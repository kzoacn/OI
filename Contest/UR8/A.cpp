#include<bits/stdc++.h>
using namespace std;
int n,m;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int a[100001],b[100001];
void bfs(){
	int xs,ys,xe,ye;scanf("%d%d%d%d",&xs,&ys,&xe,&ye);
	static int d[101][101];
	memset(d,0,sizeof d);
	deque<pair<int,int> >q;
	q.push_back(make_pair(xs,ys));d[xs][ys]=1;
	while(!q.empty()){
		int x=q.front().first;
		int y=q.front().second;q.pop_front();
		for(int k=0;k<4;k++){
			int i=dx[k]+x,j=dy[k]+y;
			if(i<1)i=n;if(i>n)i=1;
			if(j<1)j=m;if(j>m)j=1;
			if(d[i][j])continue;
			int w=(a[x]^b[y])^(a[i]^b[j]);			
			d[i][j]=d[x][y]+w;
			if(w)q.push_back(make_pair(i,j));
			else q.push_front(make_pair(i,j));			
		}
	}printf("%d\n",d[xe][ye]-1);
}
void BF(){
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);		
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);	
	int q;scanf("%d",&q);
	while(q--)
		bfs();
}
const int BIT=18;
int st[100001][18];
int mi(int x){if(x>n)return x-n;return x;}
void solve(){
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);		
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);	
	for(int i=1;i<=n;i++)a[i]^=b[1];
	for(int i=1;i<n;i++)st[i][0]=(a[i]^a[i+1]);
	st[n][0]=(a[1]^a[n]);
	for(int j=1;j<BIT;j++)
	for(int i=1;i<=n;i++)
	st[i][j]=st[i][j-1]+st[mi(i+(1<<(j-1)))][j-1];
	int q;scanf("%d",&q);
	while(q--){
		int l,r;scanf("%d%*d%d%*d",&l,&r);
		if(l>r)swap(l,r);
		int _l=l,_r=r;
		if(l==r)puts("0");
		else{
			int ans1=0;
			for(int i=BIT-1;i>=0;i--)if(l+(1<<i)<=r)
				ans1+=st[l][i],l+=1<<i;
			l=_l;r=_r;
			int ans2=0;
			l+=n;
			for(int i=BIT-1;i>=0;i--)if(r+(1<<i)<=l)
				ans2+=st[r][i],r+=1<<i;
			printf("%d\n",min(ans1,ans2));
		}
	}
}
int main(){
	freopen("A.in","r",stdin);
	scanf("%d%d",&n,&m);
	if(n<=100&&m<=100)
		BF();
	else solve();
	return 0;
}
