#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int BIT = 177147+10;
int n,m;
int scan(){
	char cc=' ';int re=0,fh=1;
	while(cc==' '||cc=='\r'||cc=='\n')cc=getchar();
	if(cc=='+')cc=getchar(),fh=1;
	if(cc=='-')cc=getchar(),fh=-1;
	while('0'<=cc&&cc<='9'){
		re=re*10+cc-'0';
		cc=getchar();
	}return re*fh;
}
struct state{
	int i,d;
	state(){}
	state(int ii,int dd):i(ii),d(dd){}
};
queue<state>dui;

const int LEN = 10+1;
const int L = 10000;
struct Big{
	int d[LEN],len;
	Big(){memset(d,0,sizeof(d));len=1;}
	Big operator = (int a){if(!a){*this = Big();return *this;}for(len=0;a;a/=L) d[++len] = a%L;}
	void print(){printf("%d",d[len]);for(int i=len-1;i;i--)printf("%04d",d[i]);}
};
typedef Big BIG;
Big operator + (Big &A,Big &B){
	Big C;C.len = max(A.len,B.len)+1;
	for(int i=1;i<=C.len;i++){
		C.d[i] += A.d[i] + B.d[i];
		if(C.d[i] >= L){
			C.d[i+1] = C.d[i]/L;
			C.d[i]%=L;
		}
	}while(C.len > 1 && C.d[C.len]==0)C.len--;
	return C;
}
BIG ans,f[2][BIT];
short v[2][BIT];
int pos(int x,int y){return (y-1)*m + x-1;}
void list(int x,short a[]){
	for(int i=1;i<=m+1;i++) a[i] = 0;
	for(int i=1;x;i++,x=x/3)
		a[i] = x%3;
}
int zip(short a[],int x,int val1,int val2){
	int re=0;
	for(int i=m+1;i;i--)
	if(i==x) re=re*3+val1;
	else if(i==x+1)re=re*3+val2;
	else re=re*3+a[i];
	return re;
}
short lin[12];
void pipei(int x,short a[],short type){
	int i,j,p1=0,p2=0;
	if(type==1){
		for(j=0,i=x+2;i<=m+1;i++){
			if(a[i]==2)j++;
			if(a[i]==1)j--;
			if(j>0&&!p1)p1=i,j--;
			if(j>0&&p1){p2=i;break;}
		}
	}else{//type == 2
		for(j=0,i=x-1;i;i--){
			if(a[i]==1)j++;
			if(a[i]==2)j--;
			if(j>0&&!p2)p2=i,j--;
			if(j>0&&p2){p1=i;break;}
		}
	}a[p1]=1;a[p2]=2;
}
void update(int i,int zt,BIG &val,short upans=0){
	i++;int i2 = i%2;
	if(!upans){
		if(v[i2][zt]!=i)f[i2][zt]=0,v[i2][zt]=i,dui.push(state(i,zt));
		f[i2][zt] = f[i2][zt]+val;
	}else ans = ans + val;
}
short map[21][21];
bool lerror(short a[]){
	int i,j;
	for(i=1,j=0;i<=m+1;i++){
		if(a[i]==1) j++;
		if(a[i]==2) j--;
		if(j<0)return 1;
	}
	return j != 0;
}
int main(){
	//freopen("input.txt","r",stdin);
	int i,j,end;
	m=scan();n=scan();
	end = pos(m,n);
	//x = 1~m y = 1~n 
	dui.push(state(0,0));
	f[0][0] = 1;
	v[0][0] = 1;
	for(i=1;i<=m;i++)
	for(j=1;j<=n;j++)
		map[i][j]=1;
	while(!dui.empty()){
		state now = dui.front();dui.pop();
		int x,y,tmp;i = now.i;
		BIG &last = f[i%2][now.d];
		if(i%m==0) now.d *= 3;
		x = i%m+1;y = i/m+1;
		list(now.d,lin);
		//if(lerror(lin))	printf("ERROR");
		if(lin[x] == 1 && lin[x+1]==2){//at end
			if(i == end) update(i,0,last,1);
		}else if(lin[x] == 2&&lin[x+1]==1){
			tmp = zip(lin,x,0,0);
			update(i,tmp,last);
		}else if(lin[x]==0&&lin[x+1]==0){
			if(map[x][y+1]&&map[x+1][y]){//*
				tmp = zip(lin,x,1,2);
				update(i,tmp,last);
			}
		}else if(lin[x]==0){
			if(map[x+1][y]){
				tmp = zip(lin,x,0,lin[x+1]);
				update(i,tmp,last);
			}
			if(map[x][y+1]){
				tmp = zip(lin,x,lin[x+1],0);
				update(i,tmp,last);
			}
		}else if(lin[x+1]==0){
			if(map[x+1][y]){
				tmp = zip(lin,x,0,lin[x]);
				update(i,tmp,last);
			}
			if(map[x][y+1]){
				tmp = zip(lin,x,lin[x],0);
				update(i,tmp,last);
			}
		}else if(lin[x]==lin[x+1]){//getpipei
			pipei(x,lin,lin[x]);
			tmp = zip(lin,x,0,0);
			update(i,tmp,last);
		}
	}
	ans = ans+ans;
	if(ans.len == 1&&ans.d[1] == 0) ans=1;//??? 
	ans.print();
	return 0;
}
