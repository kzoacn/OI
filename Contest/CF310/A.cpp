#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,k,b;
int ans=0;
vector<int>a[maxn*2];
int siz;
int one[maxn];
int bel[maxn];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++){
		int m;scanf("%d",&m);
		for(int j=0;j<m;j++){
			int x;scanf("%d",&x);
			a[i].push_back(x);
			bel[x]=i;
			if(m==1)one[x]=1;
		}
	}
	
	int now=0;
	if(a[bel[1]].front()!=1){
		int b=bel[1];
		while(a[b].size()){
			ans++;
			int bc=a[b].back();
			a[b].pop_back();
			one[bc]=1;
			bel[bc]=k++;
			a[k-1].push_back(bc);	
		}
		now=1;
	}else{
		now=1;
		int b=bel[1];
		for(int i=1;i<a[b].size();i++)
			if(a[b][i-1]+1==a[b][i])now++;
			else break;
		while(a[b].back()!=now){
			ans++;
			int bc=a[b].back();
			a[b].pop_back();
			one[bc]=1;
			bel[bc]=k++;
			a[k-1].push_back(bc);
		}		
	}
	for(int i=now+1;i<=n;i++){
		if(one[i])now++,ans++;
		else{
			int b=bel[i];
			while(a[b].back()!=i){
				ans++;
				int bc=a[b].back();
				a[b].pop_back();
				one[bc]=1;
				bel[bc]=k++;
				a[k-1].push_back(bc);
			}
			now++;
			if(a[b].size()==1)ans++;
			else ans+=2;
			a[b].pop_back();
		}
	}cout<<ans<<endl;
	return 0;
}
