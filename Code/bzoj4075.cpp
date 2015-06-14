#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>vec[26];
int ans[26][26];
char str[26];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int m;scanf("%d",&m);
		while(m--){
			scanf("%s",str);
			int t=0,l=strlen(str);
			for(int j=0;j<l;j++)t|=1<<(str[j]-'a');
			vec[i].push_back(t);
		}
	}memset(ans,-1,sizeof ans);
	for(int j=0;j<n;j++){
		int s=1<<j;
		ans[j][j]=0;
		for(int cnt=1;cnt<n;cnt++){
			int ns=s;
			for(int i=0;i<n;i++)if(ans[i][j]==-1){
				int ok=0;
				for(int k=0;k<vec[i].size();k++){
					if((s&vec[i][k])==vec[i][k]){
						ok=1;break;
					}
				}
				if(ok){
					ns|=1<<i;
					ans[i][j]=cnt;
				}
			}s=ns;
		}
	}for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	printf("%d%c",ans[i][j]," \n"[j+1==n]);
	return 0;
}
