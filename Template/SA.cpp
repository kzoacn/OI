#include<bits/stdc++.h>
#define fst first
#define sec second
using namespace std;
typedef pair<int,int> pi;
const int maxn=1e6+205;
pi tmp[maxn];
int sa[maxn],rank[maxn],height[maxn],n,len,len2;
char s[maxn];
int sum[maxn],lef[maxn],rig[maxn];
void radix_sort(int n,pi *a,int *rank,int *sa){
	int m=max(n,27);
	memset(sum,0,sizeof(int)*(m+1));
	for(int i=1;i<=n;i++)sum[a[i].sec]++;
	for(int i=1;i<=m;i++)sum[i]+=sum[i-1];
	for(int i=n;i>=1;i--)rank[i]=sum[a[i].sec]--;
	for(int i=1;i<=n;i++)sa[rank[i]]=i;
	memset(sum,0,sizeof(int)*(m+1));
	for(int i=1;i<=n;i++)sum[a[i].fst]++;
	for(int i=1;i<=m;i++)sum[i]+=sum[i-1];
	for(int i=n;i>=1;i--)rank[sa[i]]=sum[a[sa[i]].fst]--;
	for(int i=1;i<=n;i++)sa[rank[i]]=i;rank[sa[1]]=1;
	for(int i=2;i<=n;i++)rank[sa[i]]=rank[sa[i-1]]+(a[sa[i]]!=a[sa[i-1]]);
}
void sa_init(int n){
	for(int i=1;i<=n;i++)tmp[i].fst=s[i]-'a'+1,tmp[i].sec=0;
	radix_sort(n,tmp,rank,sa);int mx=0;
	for(int j=1;j<=n;j<<=1){
		for(int i=1;i<=n;i++)tmp[i].fst=rank[i],tmp[i].sec=i+j<=n?rank[i+j]:0,mx=max(mx,rank[i]);
		if(mx==n)break;radix_sort(n,tmp,rank,sa);
	}for(int i=1,j,k=0;i<=n;i++){
		k-=!!k;j=sa[rank[i]-1];
		while(s[i+k]==s[j+k])k++;
		height[rank[i]]=k;
	}
}
int Qsum(int L,int R){
	int l=1,r=len,ans=0;
	while(l<r){
		int mid=(l+r)>>1;
		int res=0;
		for(int i=L;i<=R;i++){
			if(sa[mid]+i-L>len){res=1;break;}
			if(s[i]<s[sa[mid]+i-L]){res=-1;break;}
			if(s[i]>s[sa[mid]+i-L]){res=1;break;}
		}if(res>=0)l=mid+1;
		else r=mid;
	}ans=l;
	l=1,r=len;
	while(l<r){
		int mid=(l+r)>>1;
		int res=0;
		for(int i=L;i<=R;i++){
			if(sa[mid]+i-L>len){res=1;break;}
			if(s[i]<s[sa[mid]+i-L]){res=-1;break;}
			if(s[i]>s[sa[mid]+i-L]){res=1;break;}
		}if(res>0)l=mid+1;
		else r=mid;
	}return ans-l;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		lef[i]=len+1;
		char c=getchar();
		while(!isalpha(c))c=getchar();
		while(isalpha(c))s[++len]=c,c=getchar();		
		rig[i]=len;s[++len]='{';
	}sa_init(len);
	for(int i=1;i<=n;i++)
		printf("%d\n",Qsum(lef[i],rig[i]));	
	return 0;
}
