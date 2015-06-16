#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,A,B,C,a;
int main(){
	scanf("%d%d%d%d%d",&n,&A,&B,&C,&a); 
	double ans=0;int _a=a;
	for (int i=2;i<=n;i++){
		int b = ((long long)a * A + B) % 100000001;
		ans+=min((a%C+1),(b%C+1))/double(LL(a%C+1)*(b%C+1));
		a=b;
	}ans+=min((a%C+1),(_a%C+1))/double(LL(a%C+1)*(_a%C+1));
	printf("%.3lf\n",ans);
	return 0;
}

