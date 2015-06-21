#include<bits/stdc++.h>
using namespace std;
int n=60,m;
struct edge{
	int u,v,w;
};
vector<edge>E;
void add(int u,int v,int w){
	assert(0<=v&&v<=n-1);
	E.push_back((edge){u,v,w});
}
void out(){
	cout<<n<<endl;
	cout<<E.size()<<endl;
	for(int i=0;i<E.size();i++)
		cout<<E[i].u<<" "<<E[i].v<<" "<<E[i].w<<endl;
}
int main(){
	freopen("d.in","w",stdout);
	int ten[15];
	ten[0]=1;
	int W[10];
	W[0]=10;
	W[1]=1e3;
	W[2]=1e5;
	W[3]=1e7;
	W[4]=2e9;
	for(int i=1;i<10;i++)ten[i]=ten[i-1]*10;
	for(int i=0;i<50;i+=10)
		add(i,i+10,INT_MAX);
	for(int i=0;i<5;i++){
		for(int j=1;j<=9;j++){
			int w=W[4-i];
			add(10*i,10*i+j,w+j);
			add(10*i+j,10*(i+1),-(w+j)-j);
		}
	}
	
	for(int i=51;i<n;i++)add(50,i,0);
	out();
	return 0;
}
