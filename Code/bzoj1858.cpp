#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
char a[maxn];
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int n,m;
void putint(int x){
	if(x<10)putchar(x+'0');
	else{putint(x/10);putchar(x%10+'0');}
}
typedef unsigned int uint;
uint one[33];
uint bitcnt[65537];
uint lw(uint x){return x&(x^(x-1));}
uint popcnt(uint x){return bitcnt[x&65535u]+bitcnt[x>>16];}
//register 
struct BITSET{
	uint a[32768];
	uint get(int x){return a[x>>5]&(1u<<(x&31));}
	void set(int x){a[x>>5]|=(1u<<(x&31));}
	void reset(int x){a[x>>5]&=~(1u<<(x&31));}
	void rev(int x){a[x>>5]^=(1u<<(x&31));}
	void set(int l,int r){
		if(!((l>>5)^(r>>5))){
			a[l>>5]|=one[r-l+1]<<(l&31);
			//for(int i=l;i<=r;i++)set(i);
		}else{
//			while(l&31)set(l++);
//			while(~(r&31))set(--r);
			a[l>>5]|=one[(31^(l&31))+1]<<(l&31);
			a[r>>5]|=one[(r&31)+1];
			memset(a+(l>>5)+1,-1,sizeof(uint)*((r>>5)-(l>>5)-1));
		}
	}
	void reset(int l,int r){
		if(!((l>>5)^(r>>5)))
			a[l>>5]&=~(one[r-l+1]<<(l&31));
		else{
			a[l>>5]&=~(one[(31^(l&31))+1]<<(l&31));
			a[r>>5]&=~(one[(r&31)+1]);
			memset(a+(l>>5)+1,0,sizeof(uint)*((r>>5)-(l>>5)-1));
		}
	}
	void rev(int l,int r){
		if(!((l>>5)^(r>>5))){
			a[l>>5]^=one[r-l+1]<<(l&31);
		}else{
			a[l>>5]^=one[(31^(l&31))+1]<<(l&31);
			a[r>>5]^=one[(r&31)+1];
			for(register int i=(l>>5)+1;i<(r>>5);i++)a[i]=~a[i];
		}	
	}
	int count(int l,int r){
		int ans=0;
		if(!((l>>5)^(r>>5)))
			ans+=popcnt(a[l>>5]&(one[r-l+1]<<(l&31)));
		else{
			ans+=popcnt(a[l>>5]&(one[(31^(l&31))+1]<<(l&31)));
			ans+=popcnt(a[r>>5]&(one[(r&31)+1]));
			for(register int i=(l>>5)+1;i<(r>>5);i++)ans+=popcnt(a[i]);
		}return ans;
	}
}bs;
int main(){
	n=getint();m=getint();
	for(int i=1;i<(1<<16);i++)bitcnt[i]=bitcnt[i>>1]+(i&1);
	for(int i=1;i<33;i++)one[i]=one[i-1]|(1<<i-1);
	for(int i=0;i<n;i++){
		if(getint())bs.set(i);
		else bs.reset(i);
	}
	while(m--){
		int op=getint();int l=getint(),r=getint();
		if(op==0){
			bs.reset(l,r);
		}else if(op==1){
			bs.set(l,r);
		}else if(op==2){
			bs.rev(l,r);	
		}else if(op==4){
			int ans=0,tmp=0;
			for(register int i=l;i<=r;i++){
				if(bs.get(i))tmp++;
				else ans=max(ans,tmp),tmp=0;
			}putint(max(ans,tmp));puts("");
		}else{
			putint(bs.count(l,r)),puts("");
		}//for(int i=0;i<n;i++)printf("%d%c",!!bs.get(i)," \n"[i+1==n]);
	}	
	return 0;
}
