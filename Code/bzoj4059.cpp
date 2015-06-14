#include<bits/stdc++.h>
using namespace std;
int n;
int a[200001],v[200001],pre[200001],nxt[200001],tmp[200001];
int getn(){
	int re=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))re=re*10+c-'0',c=getchar();
	return re;
}
bool dfs(int l,int r){
	if(l>=r)return 1;
	int len=(r-l+1),i=l,j=r;
	while(len--){
		if(len&1){
			if(pre[j]<l&&nxt[j]>r)
				return dfs(l,j-1)&&dfs(j+1,r);
			j--;
		}else{			
			if(pre[i]<l&&nxt[i]>r)
				return dfs(l,i-1)&&dfs(i+1,r);
			i++;

		}
	}return 0;
}
void solve(){
	n=getn();
	//for(int i=1;i<=n;i++)a[i]=getn(),v[i]=a[i];
	int *ed=a+1+n;
	for(int *i=a+1,*j=v+1;i!=ed;i++,j++)
		*i=getn(),*j=*i;
	sort(v+1,v+1+n);
	int siz=unique(v+1,v+1+n)-v-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(v+1,v+1+siz,a[i])-v;
	for(int i=1;i<=siz;i++)tmp[i]=0;
	for(int i=1;i<=n;i++)
		pre[i]=tmp[a[i]],tmp[a[i]]=i;
	for(int i=1;i<=siz;i++)tmp[i]=n+1;
	for(int i=n;i>=1;i--)
		nxt[i]=tmp[a[i]],tmp[a[i]]=i;	
	puts(dfs(1,n)?"non-boring":"boring");
}
int main(){
	int T=getn();
	while(T--)solve();
	return 0;
}

