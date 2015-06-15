#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<cmath> 
#include<algorithm> 
#include<ctime> 
#define MAXN 1000010 
#define MAXM 1000010 
#define MOD 100000007 
using namespace std; 
typedef long long LL; 
int n,m; 
LL G[MAXM]={1},F[MAXM],Two[MAXN]={1},ans; 
LL power(LL n,LL p) 
{ 
    LL ans=1; 
	    while(n) 
		    { 
			        if(n&1) ans=ans*p%MOD; 
					        p=p*p%MOD,n>>=1; 
							    } 
								    return ans; 
									} 
									void Dp() 
									{ 
									    for(int i=1;i<=n;i++) 
										        Two[i]=Two[i-1]*2%MOD; 
												    for(int i=1;i<=m;i++) 
													        G[i]=G[i-1]*(Two[n]-i)%MOD; 
															    for(int i=3;i<=m;i++) 
																        F[i]=(G[i-1]-F[i-1]-F[i-2]*(i-1)%MOD*((Two[n]-i+1+MOD)%MOD)%MOD+2*MOD)%MOD; 
																		    ans=F[m]; 
																			    LL jcm=1; 
																				    for(int i=1;i<=m;i++) 
																					        jcm=jcm*i%MOD; 
																							    ans=ans*power(MOD-2,jcm)%MOD; 
																								} 
																								int main() 
																								{ 
																								    scanf("%d %d",&n,&m); 
																									    Dp(); 
																										    printf("%lld\n",ans); 
																											    return 0; 
																												}

