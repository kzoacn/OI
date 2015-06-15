#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m,L[maxn],F[maxn],cnt[maxn],nxt[maxn];
deque<int>dq[maxn];
vector<int>anss;
int main(){
	n=in();m=in();
	for(int i=1;i<=n+1;i++)F[i]=L[i]=in();
	sort(F+1,F+2+n);
	for(int i=1;i<=n+1;i++)dq[F[i]].push_back(i);
	for(int i=1;i<=n+1;i++)nxt[i]=dq[L[i]].front(),dq[L[i]].pop_front();
	for(int i=1,j=1;i<=n;i++,j=nxt[j])
		anss.push_back(L[j]);
	reverse(anss.begin(),anss.end());
	for(int i=0;i<n;i++)printf("%d ",anss[i]);
	return 0;
}
