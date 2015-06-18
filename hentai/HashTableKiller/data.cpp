#include<bits/stdc++.h>
using namespace std;
unsigned long mo[] =
    {
      5ul,          53ul,         97ul,         193ul,       389ul,
      769ul,        1543ul,       3079ul,       6151ul,      12289ul,
      24593ul,      49157ul,      98317ul,      196613ul,    393241ul,
      786433ul,     1572869ul,    3145739ul,    6291469ul,   12582917ul,
      25165843ul,   50331653ul,   100663319ul,  201326611ul, 402653189ul,
      805306457ul,  1610612741ul, 3221225473ul, 4294967291ul
    };
int main(){
	freopen("in","w",stdout);
	int n=5e4;
	printf("%d\n",n);
	int cur=0,cnt=155/2+1,now=25705;
	for(int i=1;i<=n;i++){
		printf("%lld\n",(long long)now*cnt);
		if(!--cnt){
			if(cur==0)cnt=582/2+1,now=75077;
			if(cur==1)now=1186567,cnt=2312/2+1;
			
			cur++
		}
	}
	return 0;
}
