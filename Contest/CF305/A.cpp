#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;
int m;
int h1,a1,x1,y1;
int h2,a2,x2,y2;
int vis1[int(1e6)],vis2[int(1e6)];
int cir1=-1,cir2=-1;
int fir1=-1,fir2=-1;
bool calc(LL s){
	LL step=vis1[a1]+s;
	return (step-vis2[a2])%cir2==0;
}
int main(){
	cin>>m;
	cin>>h1>>a1;
	cin>>x1>>y1;
	cin>>h2>>a2;
	cin>>x2>>y2;
	int H1=h1,H2=h2;
	for(int i=1;i<=m*3;i++){
//		cout<<H1<<" "<<H2<<endl;
		H1=((LL)H1*x1+y1)%m;
		H2=((LL)H2*x2+y2)%m;
		if(cir1!=-1&&fir1==-1&&H1==a1)fir1=i;
		if(cir2!=-1&&fir2==-1&&H2==a2)fir2=i;
		if(H1==a1&&H2==a2)return printf("%d\n",i),0;
		if(H1==a1&&vis1[H1]){if(!~cir1)cir1=i-vis1[H1];}else vis1[H1]=i;
		if(H2==a2&&vis2[H2]){if(!~cir2)cir2=i-vis2[H2];}else vis2[H2]=i;
	}
	if(fir1==-1||fir2==-1)return puts("-1"),0;
	for(int i=0;i<m;i++)if(calc((LL)i*cir1)){
		cout<<vis1[a1]+(LL)i*cir1<<endl;
		return 0;
	}
	cout<< -1 <<endl;
	return 0;
}

