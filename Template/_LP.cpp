#define rep(i,n) for(int i=0;i<(n);i++)
#define ft(i,x,y) for(int i=(x);i<=(y);i++)
void orz(int a,int b)
{
    ft(i,0,m) if (i!=a&&fabs(A[i][b])>0) ft(j,0,n) if (j!=b) A[i][j]-=A[a][j]*A[i][b]/A[a][b];
    ft(j,0,n) if (j!=b) A[a][j]/=A[a][b];
    ft(i,0,m) if (i!=a) A[i][b]/=-A[a][b];
    A[a][b]=1/A[a][b];
}double simplex(){
        for(;;){
                int ii=1,jj=0;
                ft(i,1,m)if(A[i][n]<A[ii][n])ii=i;
                if(A[ii][n]>=0)break;
                rep(i,n)if(A[ii][i]<A[ii][jj])jj=i;
                if(A[ii][jj]>=0)return -1e99;
                orz(ii,jj);
        }for(;;){
                 int ii=1,jj=0;
                 rep(j,n)if(A[0][j]<A[0][jj])jj=j;
                 if(A[0][jj]>=0)break;
                 ft(i,1,m)if(A[i][jj]>0&&(A[ii][jj]<=0||A[i][n]/A[i][jj]<A[ii][n]/A[ii][jj]))ii=i;
                 if(A[ii][jj]<=0)return 1e99;
                 orz(ii,jj);
            }
        return A[0][n];
}
