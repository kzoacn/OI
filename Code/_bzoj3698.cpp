#include<cstdio>
#include<cstring>
const int MAXN=210,MAXM=10010,oo=1<<30;
int la[MAXN],et=1,s,t,d[MAXN],p[MAXN],q[MAXM],l,r;bool in[MAXN];
struct E{int from,to,flow,cost,nxt;}e[MAXM<<1];
void add(int from,int to,int flow,int cost){
	e[++et]=(E){from,to,flow,cost,la[from]};la[from]=et;
	e[++et]=(E){to,from,0,-cost,la[to]};la[to]=et;
}
bool spfa(){
	memset(d,127,sizeof(d));int i,tmp;
	for(q[l=r=1]=s,d[s]=0,in[s]=1;l<=r;in[q[l++]]=0)
	for(i=la[q[l]];i;i=e[i].nxt)
	if(e[i].flow&&d[e[i].to]>(tmp=d[q[l]]+e[i].cost))
		d[e[i].to]=tmp,p[e[i].to]=i,
		!in[e[i].to]?in[q[++r]=e[i].to]=1:1;
	return d[t]<oo;
}
int mcf(){
	int flow,cost=0,u;
	while(spfa()){
		for(flow=oo,u=t;u!=s;u=e[p[u]].from)
		flow>e[p[u]].flow?flow=e[p[u]].flow:1;
		for(u=t;u!=s;u=e[p[u]].from)
		e[p[u]].flow-=flow,e[p[u]^1].flow+=flow;
		cost+=flow*d[t];
	}
	return cost;
}
double a[110][110];int n,sum;
int main()
{
	scanf("%d",&n);int i,j,tmp;s=n+n+1;t=s+1;
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%lf",&a[i][j]),sum+=(int)a[i][j];
	for(i=1;i<n;i++)
	for(j=1;j<n;j++)
	{
		tmp=(int)a[i][j];a[i][j]-=tmp;
		a[i][n]-=tmp;a[n][j]-=tmp;
		if(a[i][j]>0)add(i,j+n,1,1);
	}
	for(i=1;i<n;i++)
	{
		tmp=(int)a[i][n];add(s,i,tmp,0);
		if(tmp!=a[i][n])add(s,i,1,1);
		tmp=(int)a[n][i];add(i+n,t,tmp,0);
		if(tmp!=a[n][i])add(i+n,t,1,1);
	}
	printf("%d\n",mcf()+sum);
}
