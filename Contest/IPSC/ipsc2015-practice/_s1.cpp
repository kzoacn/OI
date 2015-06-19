#include<bits/stdc++.h>
using namespace std;
deque<pair<int,int> >dq;
int c[4];
void Do(){
	deque<pair<int,int> >d;
	for(int i=0;i<dq.size();i++){
		int x=dq[i].first,y=dq[i].second;		
		if(c[x]+1==y){
			c[x]=y;
		}else d.push_back(make_pair(x,y));
	}reverse(d.begin(),d.end());
	dq=d;
}
void sol(){
	int n;scanf("%d",&n);
	c[0]=c[1]=c[2]=c[3]=0;
	dq.clear();
	for(int i=1;i<=n*4;i++){
		char s[10];
		int x;
		scanf("%s",s);
		char c=s[0];
		sscanf(s+1,"%d",&x);
		if(c=='H')c=0;
		if(c=='D')c=1;
		if(c=='S')c=2;
		if(c=='C')c=3;
		dq.push_back(make_pair(c,x));
	}int ans=0;
	while(dq.size())
		Do(),ans++;
	cout<<ans<<endl;
} 
int main(){
	freopen("in","r",stdin);
//	freopen("s1.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)sol();
	return 0;
}
