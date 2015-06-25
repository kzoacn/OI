void Gauss(){
	int r,k;
	for(int i=0;i<n;i++){
		r=i;
		for(int j=i+1;j<n;j++)
			if(fabs(A[j][i])>fabs(A[r][i]))r=j;
		if(r!=i)for(int j=0;j<=n;j++)swap(A[i][j],A[r][j]);
		for(int k=i+1;k<n;k++){
			double f=A[k][i]/A[i][i];
			for(int j=i;j<=n;j++)A[k][j]-=f*A[i][j];
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++)
			A[i][n]-=A[j][n]*A[i][j];
		A[i][n]/=A[i][i];
	}
	for(int i=0;i<n-1;i++)
		cout<<fixed<<setprecision(3)<<A[i][n]<<" ";
	cout<<fixed<<setprecision(3)<<A[n-1][n];		
}
bool Gauss(){
	for(int i=1;i<=n;i++){
		int r=0;
		for(int j=i;j<=m;j++)
		if(a[j][i]){r=j;break;}
		if(!r)return 0;
		ans=max(ans,r);
		swap(a[i],a[r]);
		for(int j=i+1;j<=m;j++)
		if(a[j][i])a[j]^=a[i];
	}for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)if(a[i][j])
		a[i][n+1]=a[i][n+1]^a[j][n+1];
	}return 1;
}
LL Gauss(){
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)A[i][j]%=m;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)A[i][j]=(A[i][j]+m)%m;
	LL ans=n%2?-1:1;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			while(A[j][i]){
				LL t=A[i][i]/A[j][i];
				for(int k=0;k<n;k++)
				A[i][k]=(A[i][k]-A[j][k]*t%m+m)%m;
				swap(A[i],A[j]);
				ans=-ans;
			}
		}ans=ans*A[i][i]%m;
	}return (ans%m+m)%m;
}
