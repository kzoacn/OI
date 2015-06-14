#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+1;
int next[maxn],n;
char s[maxn];
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=2,j=0;i<=n;i++){
		while(j&&s[i]!=s[j+1])j=next[j];
		next[i]=j+=s[i]==s[j+1];
	}long long ans=0;
	for(int i=1;i<=n;i++)if(next[next[i]])next[i]=next[next[i]];
	for(int i=1;i<=n;i++)if(next[i])ans+=i-next[i];
	cout<<ans<<endl;
	return 0;
}
