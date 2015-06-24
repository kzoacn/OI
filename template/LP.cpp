int dcmp(double x){return (x>1e-6)-(x<-1e-6);}
int n,m,X;
void pivot(int l,int e){
	for(int i=0;i<=n;i++)if(i!=e)
		a[l][i]/=a[l][e];
	a[l][e]=1/a[l][e];
	for(int i=0;i<=m;i++)if(i!=l){
		if(dcmp(a[i][e])==0)continue;
		for(int j=0;j<=n;j++)if(j!=e)
			a[i][j]-=a[i][e]*a[l][j];
		a[i][e]*=-a[l][e];
	}
}
double simplex(){
	while(1){
		int l=1,e=1;
		for(int i=1;i<=m;i++)if(a[i][0]<a[l][0])l=i;
		if(dcmp(a[l][0])>=0)break;
		for(int i=1;i<=n;i++)if(a[l][i]<a[l][e])e=i;
		if(dcmp(a[l][e])>=0){puts("-1");exit(0);}
		pivot(l,e);
	}
	while(1){
		int l=1,e=1;
		for(int i=1;i<=n;i++)if(a[0][i]>a[0][e])e=i;
		if(dcmp(a[0][e])<=0)return -a[0][0];
		for(int i=1;i<=m;i++)if(dcmp(a[i][e])>0&&(a[l][e]<=0||a[i][0]*a[l][e]<a[l][0]*a[i][e]))l=i;
		if(dcmp(a[l][e])<=0){puts("-1");exit(0);}
		pivot(l,e);		
	}
}
//标准型
//a[0][1..n]表示z 
//a[i][1..n]表示约束
//m为约束个数、n为变量数 
